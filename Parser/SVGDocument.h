#pragma once

#include "SVGElement.h"
#include <vector>
#include <memory>
#include <QString>
#include <map>
#include <string>

class SVGDocument {
public:
    SVGDocument(int width = 800, int height = 600);
    
    // Add an element to the document
    void addElement(std::shared_ptr<SVGElement> element);
    
    // Get all elements
    const std::vector<std::shared_ptr<SVGElement>>& getElements() const;
    
    // Dimension getters
    int getWidth() const;
    int getHeight() const;
    bool hasWidth() const;
    bool hasHeight() const;
    
    // ViewBox
    QString getViewBox() const;
    bool hasViewBox() const;
    void setViewBox(const QString& viewBox);
    
    // Attributes
    const std::map<std::string, std::string>& getAttributes() const;
    void setAttribute(const std::string& key, const std::string& value);
    
    // Clear all elements
    void clear();

private:
    std::vector<std::shared_ptr<SVGElement>> elements_;
    int width_;
    int height_;
    bool hasWidth_;
    bool hasHeight_;
    QString viewBox_;
    bool hasViewBox_;
    std::map<std::string, std::string> attributes_;
};
