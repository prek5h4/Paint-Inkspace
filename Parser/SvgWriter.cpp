#include "SVGWriter.h"
#include <stdexcept>

std::string SVGWriter::writeSVG(const SVGDocument& document, const QString& filename) {
    std::ofstream out(filename.toStdString());
    
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename.toStdString());
    }
    
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    writeSVGHeader(out, document);
    
    for (const auto& element : document.getElements()) {
        if (element) {
            QString svgString = element->toSVG();
            out << "  " << svgString.toStdString() << "\n";
        }
    }
    
    out << "</svg>\n";
    out.close();
    
    return filename.toStdString();
}

void SVGWriter::writeSVGHeader(std::ofstream& out, const SVGDocument& doc) {
    out << "<svg";
    out << " xmlns=\"http://www.w3.org/2000/svg\"";
    out << " version=\"1.1\"";
    
    if (doc.hasWidth()) {
        out << " width=\"" << doc.getWidth() << "\"";
    }
    if (doc.hasHeight()) {
        out << " height=\"" << doc.getHeight() << "\"";
    }
    if (doc.hasViewBox()) {
        out << " viewBox=\"" << doc.getViewBox().toStdString() << "\"";
    }
    
    writeAttributes(out, doc.getAttributes());
    out << ">\n";
}

void SVGWriter::writeElement(std::ofstream& out, const SVGElement& elem, int indentLevel) {
    std::string indent(indentLevel * 2, ' ');
    out << indent;
    QString svgString = elem.toSVG();
    out << svgString.toStdString() << "\n";
}

void SVGWriter::writeAttributes(std::ofstream& out, const std::map<std::string, std::string>& attrs) {
    for (const auto& [key, value] : attrs) {
        out << " " << key << "=\"" << escapeAttributeValue(value) << "\"";
    }
}

std::string SVGWriter::escapeAttributeValue(const std::string& value) {
    std::string escaped;
    escaped.reserve(value.size());
    
    for (char c : value) {
        switch (c) {
            case '&':  escaped += "&amp;"; break;
            case '<':  escaped += "&lt;"; break;
            case '>':  escaped += "&gt;"; break;
            case '"':  escaped += "&quot;"; break;
            case '\'': escaped += "&apos;"; break;
            default:   escaped += c; break;
        }
    }
    
    return escaped;
}
