#include "SVGDocument.h"

SVGDocument::SVGDocument(int width, int height)
    : width_(width), height_(height), 
      hasWidth_(true), hasHeight_(true), 
      hasViewBox_(false) {}

void SVGDocument::addElement(std::shared_ptr<SVGElement> element) {
    if (element) {
        elements_.push_back(element);
    }
}

const std::vector<std::shared_ptr<SVGElement>>& SVGDocument::getElements() const {
    return elements_;
}

int SVGDocument::getWidth() const {
    return width_;
}

int SVGDocument::getHeight() const {
    return height_;
}

bool SVGDocument::hasWidth() const {
    return hasWidth_;
}

bool SVGDocument::hasHeight() const {
    return hasHeight_;
}

QString SVGDocument::getViewBox() const {
    return viewBox_;
}

bool SVGDocument::hasViewBox() const {
    return hasViewBox_;
}

void SVGDocument::setViewBox(const QString& viewBox) {
    viewBox_ = viewBox;
    hasViewBox_ = true;
}

const std::map<std::string, std::string>& SVGDocument::getAttributes() const {
    return attributes_;
}

void SVGDocument::setAttribute(const std::string& key, const std::string& value) {
    attributes_[key] = value;
}

void SVGDocument::clear() {
    elements_.clear();
}
