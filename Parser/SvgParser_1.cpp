#include "SvgParser.h"
#include "SVGElement.h"
#include <QRegularExpression>
//#include <iostream>

std::vector<std::pair<double, double>> SVGParser::parsePolygonPoints(const QString& pointsStr) {
    std::vector<std::pair<double, double>> points;
    
    if (pointsStr.isEmpty()) return points;
    
    QStringList pairs = pointsStr.split(' ', Qt::SkipEmptyParts);
    for (const QString& pair : pairs) {
        QStringList coords = pair.split(',');
        if (coords.size() == 2) {
            points.push_back({coords[0].toDouble(), coords[1].toDouble()});
        }
    }
    
    return points;
}

std::vector<std::pair<double, double>> SVGParser::parsePathData(const QString& pathStr) {
    std::vector<std::pair<double, double>> points;
    
    if (pathStr.isEmpty()) return points;
    
    // Parse SVG path data (supports M and L commands)
    QStringList commands = pathStr.split(QRegularExpression("[ML]"), Qt::SkipEmptyParts);
    
    for (const QString& cmd : commands) {
        QStringList coords = cmd.trimmed().split(' ', Qt::SkipEmptyParts);
        if (coords.size() >= 2) {
            points.push_back({coords[0].toDouble(), coords[1].toDouble()});
        }
    }
    
    return points;
}

SVGDocument SVGParser::parseSVG(const std::vector<XMLToken>& tokens) {
    SVGDocument document(800, 600);
    size_t pos = 0;

    //std::cout << "=== STARTING PARSE ===" << std::endl;
    
    while (pos < tokens.size()) {
        //std::cout << "Parse loop at pos=" << pos << " token type=" << static_cast<int>(tokens[pos].type)
                 // << " name='" << tokens[pos].name << "'" << std::endl;
        
        if (tokens[pos].type == XMLToken::Type::OpenTag && tokens[pos].name == "svg") {
            pos++; // Skip the svg open tag
            
            // Skip svg attributes
            while (pos < tokens.size() && tokens[pos].type == XMLToken::Type::Attribute) {
                pos++;
            }
            
            // Parse child elements
            while (pos < tokens.size() && 
                   !(tokens[pos].type == XMLToken::Type::CloseTag && tokens[pos].name == "svg")) {
                
                //std::cout << "  Child element at pos=" << pos << std::endl;
                
                if (tokens[pos].type == XMLToken::Type::OpenTag) {
                    std::shared_ptr<SVGElement> element = parseElement(tokens, pos);
                    if (element) {
                        //std::cout << "  Added element: " << element->toSVG().toStdString() << std::endl;
                        document.addElement(element);
                    } else {
                        //std::cout << "  parseElement returned null" << std::endl;
                    }
                } else {
                    //std::cout << "  Skipping non-OpenTag token" << std::endl;
                    pos++; // Skip non-element tokens
                }
            }
            
            //std::cout << "Breaking from svg content loop" << std::endl;
            break; // Exit after processing svg
        }
        pos++;
    }

    //std::cout << "Total elements: " << document.getElements().size() << std::endl;
    
    return document;
}
