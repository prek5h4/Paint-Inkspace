#include "SVGElement.h"
#include <cmath>

/* Rectangle */
SVGRectangle::SVGRectangle(double x, double y, double w, double h, const QString& c, const QString& strokeColor, double strokeWidth)
    : x_(x), y_(y), width_(w), height_(h), strokeColor_(strokeColor), fillColor_(c), strokeWidth_(strokeWidth) {}

void SVGRectangle::draw(QPainter&) const {}

QString SVGRectangle::toSVG() const {
    return QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" fill=\"%5\" stroke=\"%6\" stroke-width=\"%7\"/>")
        .arg(x_)
        .arg(y_)
        .arg(width_)
        .arg(height_)
        .arg(fillColor_)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}

/* Circle */
SVGCircle::SVGCircle(double cx, double cy, double r, const QString& c, const QString& strokeColor, double strokeWidth)
    : cx_(cx), cy_(cy), radius_(r), fillColor_(c), strokeColor_(strokeColor), strokeWidth_(strokeWidth) {}

void SVGCircle::draw(QPainter&) const {}

QString SVGCircle::toSVG() const {
    return QString("<circle cx=\"%1\" cy=\"%2\" r=\"%3\" fill=\"%4\" stroke=\"%5\" stroke-width=\"%6\"/>")
        .arg(cx_)
        .arg(cy_)
        .arg(radius_)
        .arg(fillColor_)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}

/* Line */
SVGLine::SVGLine(double x1, double y1, double x2, double y2,
                 const QString& c, double w)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2),
      strokeColor_(c), strokeWidth_(w) {}

void SVGLine::draw(QPainter&) const {}

QString SVGLine::toSVG() const {
    return QString("<line x1=\"%1\" y1=\"%2\" x2=\"%3\" y2=\"%4\" stroke=\"%5\" stroke-width=\"%6\"/>")
        .arg(x1_)
        .arg(y1_)
        .arg(x2_)
        .arg(y2_)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}

/* Round rect */
SVGRoundRect::SVGRoundRect(double x, double y, double w, double h,
                           double rx, double ry, const QString& c, const QString& strokeColor, double strokeWidth)
    : x_(x), y_(y), width_(w), height_(h),
      rx_(rx), ry_(ry), fillColor_(c), strokeColor_(strokeColor), strokeWidth_(strokeWidth) {}

void SVGRoundRect::draw(QPainter&) const {}

QString SVGRoundRect::toSVG() const {
    return QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" rx=\"%5\" ry=\"%6\" fill=\"%7\" stroke=\"%8\" stroke-width=\"%9\"/>")
        .arg(x_)
        .arg(y_)
        .arg(width_)
        .arg(height_)
        .arg(rx_)
        .arg(ry_)
        .arg(fillColor_)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}

/* Hexagon */
SVGHexagon::SVGHexagon(double cx, double cy, double s, const QString& c, const QString& strokeColor, double strokeWidth)
    : cx_(cx), cy_(cy), sidelength_(s), fillColor_(c), strokeColor_(strokeColor), strokeWidth_(strokeWidth) {}

void SVGHexagon::draw(QPainter&) const {}

QString SVGHexagon::toSVG() const {
    // Calculate hexagon points
    QString points;
    for (int i = 0; i < 6; i++) {
        double angle = M_PI / 3.0 * i;  // 60 degrees in radians
        double px = cx_ + sidelength_ * cos(angle);
        double py = cy_ + sidelength_ * sin(angle);
        
        if (i > 0) points += " ";
        points += QString("%1,%2").arg(px).arg(py);
    }
    
    return QString("<polygon points=\"%1\" fill=\"%2\" stroke=\"%3\" stroke-width=\"%4\"/>")
        .arg(points)
        .arg(fillColor_)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}

/* Text */
SVGText::SVGText(double x, double y, const QString& txt,
                 const QString& c, const QString& f, double sz)
    : x_(x), y_(y), content_(txt),
      fillColor_(c), fontFamily_(f), fontSize_(sz) {}

void SVGText::draw(QPainter&) const {}

QString SVGText::toSVG() const {
    return QString("<text x=\"%1\" y=\"%2\" fill=\"%3\" font-family=\"%4\" font-size=\"%5\">%6</text>")
        .arg(x_)
        .arg(y_)
        .arg(fillColor_)
        .arg(fontFamily_)
        .arg(fontSize_)
        .arg(content_);
}

/* Freehand */
SVGFreehand::SVGFreehand(
    const std::vector<std::pair<double, double>>& pts,
    const QString& c, double w)
    : points_(pts), strokeColor_(c), strokeWidth_(w) {}

void SVGFreehand::draw(QPainter&) const {}

QString SVGFreehand::toSVG() const {
    if (points_.empty()) {
        return "";
    }
    
    QString pathData = QString("M %1 %2").arg(points_[0].first).arg(points_[0].second);
    
    for (size_t i = 1; i < points_.size(); i++) {
        pathData += QString(" L %1 %2").arg(points_[i].first).arg(points_[i].second);
    }
    
    return QString("<path d=\"%1\" stroke=\"%2\" stroke-width=\"%3\" fill=\"none\"/>")
        .arg(pathData)
        .arg(strokeColor_)
        .arg(strokeWidth_);
}