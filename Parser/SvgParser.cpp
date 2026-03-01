#include "SVGParser.h"

std::shared_ptr<SVGElement> SVGParser::parseElement(const std::vector<XMLToken>& tokens, size_t& pos) {
    if (pos >= tokens.size() || tokens[pos].type != XMLToken::Type::OpenTag) {
        return nullptr;
    }
    
    QString tagName = QString::fromStdString(tokens[pos].name);
    pos++;
    
    // Initialize attributes
    double x = 0, y = 0, width = 0, height = 0;
    double cx = 0, cy = 0, radius = 0;
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    double rx = 0, ry = 0;
    double fontSize = 12, strokeWidth = 1;
    QString fill = "black", stroke = "black", content = "", fontFamily = "Arial";
    QString points = "";
    QString pathData = "";
    
    // Parse attributes
    while (pos < tokens.size() && tokens[pos].type == XMLToken::Type::Attribute) {
        QString attrName = QString::fromStdString(tokens[pos].name);
        QString attrValue = QString::fromStdString(tokens[pos].value);
        
        if (attrName == "x") x = attrValue.toDouble();
        else if (attrName == "y") y = attrValue.toDouble();
        else if (attrName == "width") width = attrValue.toDouble();
        else if (attrName == "height") height = attrValue.toDouble();
        else if (attrName == "cx") cx = attrValue.toDouble();
        else if (attrName == "cy") cy = attrValue.toDouble();
        else if (attrName == "r") radius = attrValue.toDouble();
        else if (attrName == "x1") x1 = attrValue.toDouble();
        else if (attrName == "y1") y1 = attrValue.toDouble();
        else if (attrName == "x2") x2 = attrValue.toDouble();
        else if (attrName == "y2") y2 = attrValue.toDouble();
        else if (attrName == "rx") rx = attrValue.toDouble();
        else if (attrName == "ry") ry = attrValue.toDouble();
        else if (attrName == "fill") fill = attrValue;
        else if (attrName == "stroke") stroke = attrValue;
        else if (attrName == "stroke-width") strokeWidth = attrValue.toDouble();
        else if (attrName == "font-size") fontSize = attrValue.toDouble();
        else if (attrName == "font-family") fontFamily = attrValue;
        else if (attrName == "points") points = attrValue;
        else if (attrName == "d") pathData = attrValue;
        
        pos++;
    }
    
    // Handle text content
    if (pos < tokens.size() && tokens[pos].type == XMLToken::Type::TextNode) {
        content = QString::fromStdString(tokens[pos].value).trimmed();
        pos++;
    }
    
    std::shared_ptr<SVGElement> element;
    
    if (tagName == "rect") {
        if (rx > 0 || ry > 0) {
            element = std::make_shared<SVGRoundRect>(x, y, width, height, rx, ry,stroke, fill, strokeWidth);
        } else {
            element = std::make_shared<SVGRectangle>(x, y, width, height, fill, stroke, strokeWidth);
        }
    } else if (tagName == "circle") {
        element = std::make_shared<SVGCircle>(cx, cy, radius, fill, stroke, strokeWidth);
    } else if (tagName == "line") {
        element = std::make_shared<SVGLine>(x1, y1, x2, y2, stroke, strokeWidth);
    } else if (tagName == "text") {
        element = std::make_shared<SVGText>(x, y, content, fill, fontFamily, fontSize);
    } else if (tagName == "polygon") {
        std::vector<std::pair<double, double>> pointsList = parsePolygonPoints(points);
        
        if (pointsList.size() == 6) {
            double sumX = 0, sumY = 0;
            for (const auto& pt : pointsList) {
                sumX += pt.first;
                sumY += pt.second;
            }
            cx = sumX / 6.0;
            cy = sumY / 6.0;
            
            double sideLength = std::sqrt(
                std::pow(pointsList[0].first - cx, 2) + 
                std::pow(pointsList[0].second - cy, 2)
            );
            
            element = std::make_shared<SVGHexagon>(cx, cy, sideLength, fill, stroke, strokeWidth  );
        }
    } else if (tagName == "path") {
        std::vector<std::pair<double, double>> pathPoints = parsePathData(pathData);
        element = std::make_shared<SVGFreehand>(pathPoints, stroke, strokeWidth);
    }
    
    // Skip to closing tag
    while (pos < tokens.size() && 
           !(tokens[pos].type == XMLToken::Type::CloseTag && 
             QString::fromStdString(tokens[pos].name) == tagName)) {
        pos++;
    }
    if (pos < tokens.size()) pos++;
    
    return element;
}