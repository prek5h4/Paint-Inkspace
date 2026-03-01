#pragma once 
#include <QString>
#include <QPainter>
#include <vector>
#include <utility>

class SVGElement{
public:
    SVGElement() = default;
    virtual ~SVGElement() = default;

    virtual void draw(QPainter& painter) const = 0;
    virtual QString toSVG() const = 0;
};

class SVGRectangle : public SVGElement {
private:
    double x_;
    double y_;
    double width_;
    double height_;
    QString fillColor_;
    QString strokeColor_; 
    double strokeWidth_;

public:
    SVGRectangle(double x, double y, double width, double height, const QString& fillColor, const QString& strokeColor, double strokeWidth);
    ~SVGRectangle() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getX() const { return x_; }
    double getY() const { return y_; }
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    QString getFill() const { return fillColor_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};

class SVGCircle : public SVGElement {
private:
    double cx_;
    double cy_;
    double radius_;
    QString fillColor_;
    QString strokeColor_;
    double strokeWidth_;

public:
    SVGCircle(double cx, double cy, double radius, const QString& fillColor, const QString& strokeColor, double strokeWidth);
    ~SVGCircle() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getCx() const { return cx_; }
    double getCy() const { return cy_; }
    double getRadius() const { return radius_; }
    QString getFill() const { return fillColor_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};

class SVGLine : public SVGElement {
private:
    double x1_;
    double y1_;
    double x2_;
    double y2_;
    QString strokeColor_;
    double strokeWidth_;

public:
    SVGLine(double x1, double y1, double x2, double y2, const QString& strokeColor, double strokeWidth);
    ~SVGLine() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getX1() const { return x1_; }
    double getY1() const { return y1_; }
    double getX2() const { return x2_; }
    double getY2() const { return y2_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};

class SVGRoundRect : public SVGElement {
private:
    double x_;
    double y_;
    double width_;
    double height_;
    double rx_;
    double ry_;
    QString fillColor_;
    QString strokeColor_;
    double strokeWidth_;
public:
    SVGRoundRect(double x, double y, double width, double height, double rx, double ry, const QString& fillColor, const QString& strokeColor, double strokeWidth);
    ~SVGRoundRect() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getX() const { return x_; }
    double getY() const { return y_; }
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    double getRx() const { return rx_; }
    double getRy() const { return ry_; }
    QString getFill() const { return fillColor_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};

class SVGHexagon : public SVGElement {
private:
    double cx_;
    double cy_;
    double sidelength_;
    QString fillColor_;
    QString strokeColor_;
    double strokeWidth_;

public:
    SVGHexagon(double cx, double cy, double sidelength, const QString& fillColor, const QString& strokeColor, double strokeWidth);
    ~SVGHexagon() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getCx() const { return cx_; }
    double getCy() const { return cy_; }
    double getSideLength() const { return sidelength_; }
    QString getFill() const { return fillColor_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};

class SVGText : public SVGElement {
private:
    double x_;
    double y_;
    QString content_;
    QString fillColor_;
    QString fontFamily_;
    double fontSize_;

public:
    SVGText(double x, double y, const QString& content, const QString& fillColor, const QString& fontFamily, double fontSize);
    ~SVGText() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    double getX() const { return x_; }
    double getY() const { return y_; }
    QString getContent() const { return content_; }
    QString getFill() const { return fillColor_; }
    QString getFontFamily() const { return fontFamily_; }
    double getFontSize() const { return fontSize_; }
};

class SVGFreehand : public SVGElement {
private:
    std::vector<std::pair<double, double>> points_;
    QString strokeColor_;
    double strokeWidth_;

public:
    SVGFreehand(const std::vector<std::pair<double, double>>& points, const QString& strokeColor, double strokeWidth);
    ~SVGFreehand() override = default;

    void draw(QPainter& painter) const override;
    QString toSVG() const override;
    
    // Getters
    const std::vector<std::pair<double, double>>& getPoints() const { return points_; }
    QString getStroke() const { return strokeColor_; }
    double getStrokeWidth() const { return strokeWidth_; }
};