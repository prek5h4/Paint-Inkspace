#include "CanvasWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <vector>

void CanvasWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(rect(), Qt::white);

    // Draw completed shapes
    for (const auto& shape : shapes_) {
    //qDebug() << "About to draw - Type:" << shape->type;
    drawShape(painter, *shape);
}

    // Draw current preview shape
    if (drawing_) {
        drawShape(painter, *currentShape_);
    }
   /* if (eraser_){
        eraseShape();
    }*/
    //draw a bounding box around the selected shape if in Move or Resize mode
    if ((currentTool_ == MoveTool || currentTool_ == ResizeTool) &&
        selectedShapeIndex_ >= 0 && selectedShapeIndex_ < shapes_.size()) {
        painter.setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        QRect bounds = selectShape(*shapes_[selectedShapeIndex_]);
        painter.drawRect(bounds.adjusted(-3, -3, 3, 3));
    }
    
}

void CanvasWidget::drawShape(QPainter& painter, const Shape& shape)
{
    painter.setPen(QPen(shape.brush_color, shape.width, Qt::SolidLine,
                        Qt::RoundCap, Qt::RoundJoin));

    painter.setBrush(QBrush(shape.fillColor));

    switch (shape.type) {

    case Shape::Rectangle: {
        int radius = shape.radius;   // For rounded rectangles, radius is set on the shape
        QRect r(shape.startPoint, shape.endPoint);
        r = r.normalized();
        painter.drawRoundedRect(r, radius, radius);
        
        break;

    }

    case Shape::Circle: {
        QPoint center = (shape.startPoint + shape.endPoint) / 2;  // Center of the bounding box
        int radius = std::min(
            std::abs(shape.endPoint.x() - shape.startPoint.x()),
            std::abs(shape.endPoint.y() - shape.startPoint.y())
        ) / 2;

        painter.drawEllipse(center, radius, radius);
        break;
    }

    case Shape::Line:
        painter.drawLine(shape.startPoint, shape.endPoint); // Draw line between start and end points
        break;

    case Shape::Hexagon: {
        QPoint center = (shape.startPoint + shape.endPoint) / 2; // Center of the bounding box

        int radius = std::min(
            std::abs(shape.endPoint.x() - shape.startPoint.x()),
            std::abs(shape.endPoint.y() - shape.startPoint.y())
        ) / 2;

        drawHexagon(painter, center, radius);
        break;
    }

    case Shape::Freehand:
        for (int i = 0; i + 1 < shape.points.size(); ++i) {
            painter.drawLine(shape.points[i], shape.points[i + 1]); //draw using continously adding points to the shape
        }
        break;

    case Shape::Text:
        painter.setFont(shape.font);   // Set the font for text
        painter.setPen(QPen(shape.brush_color));
        painter.drawText(shape.startPoint, shape.text);
        break;
    }
}

void CanvasWidget::drawHexagon(QPainter& painter,
                              const QPoint& center,
                              int radius)
{
    QPolygon hexagon;
    //compute the 6 vertices of the hexagon based on the center and radius
    for (int i = 0; i < 6; ++i) {
        double angle = M_PI / 3.0 * i;
        int x = center.x() + int(radius * std::cos(angle));
        int y = center.y() + int(radius * std::sin(angle));
        hexagon << QPoint(x, y);
    }

    painter.drawPolygon(hexagon);
}

