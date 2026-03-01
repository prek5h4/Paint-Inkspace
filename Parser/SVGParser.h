#pragma once
#include <vector>
#include <memory>
#include "XmlTokenizer.h"
#include "SVGElement.h"
#include "SVGDocument.h"

class SVGParser {
public:
    SVGParser() = default;
    ~SVGParser() = default;
    
    SVGDocument parseSVG(const std::vector<XMLToken>& tokens);
    
private:
    std::shared_ptr<SVGElement> parseElement(const std::vector<XMLToken>& tokens, size_t& pos);
    std::vector<std::pair<double, double>> parsePolygonPoints(const QString& pointsStr);
    std::vector<std::pair<double, double>> parsePathData(const QString& pathStr);
};