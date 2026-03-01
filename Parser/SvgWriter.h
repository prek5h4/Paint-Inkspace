#pragma once
#include <fstream>
#include <map>
#include "SVGDocument.h"
#include "SVGElement.h"

class SVGWriter {
public:
    SVGWriter() = default;
    ~SVGWriter() = default;

    static std::string writeSVG(const SVGDocument& document, const QString& filename);
    
private:   
    static void writeSVGHeader(std::ofstream& out, const SVGDocument& doc);
    static void writeElement(std::ofstream& out, const SVGElement& elem, int indentLevel);
    static void writeAttributes(std::ofstream& out, const std::map<std::string, std::string>& attrs);
    static std::string escapeAttributeValue(const std::string& value);
};