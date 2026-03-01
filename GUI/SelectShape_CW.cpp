#include "CanvasWidget.h" 
#include <QRect> 
#include <QPoint> 
#include <QPainterPath> 
#include <cmath>
#include <QFontMetrics>


QRect CanvasWidget::selectShape(const Shape& shape) const {
    const int SELECTION_PADDING = 8;  // Padding around shapes 
    
    switch (shape.type) {

    case Shape::Rectangle: {
        // Create bounding box around the rectangle with padding
        return QRect(shape.startPoint, shape.endPoint)
                .normalized()
                .adjusted(-SELECTION_PADDING, -SELECTION_PADDING, 
                         SELECTION_PADDING, SELECTION_PADDING);
    }

    case Shape::Circle:{
        // Create bounding box around the circle with padding
        QPoint center_ = (shape.startPoint + shape.endPoint) / 2;
        int radius = std::min(
            std::abs(shape.endPoint.x() - shape.startPoint.x()),
            std::abs(shape.endPoint.y() - shape.startPoint.y())
        ) / 2;
        return QRect(center_.x() - radius - SELECTION_PADDING,
                     center_.y() - radius - SELECTION_PADDING,
                     2 * radius + 2 * SELECTION_PADDING,
                     2 * radius + 2 * SELECTION_PADDING);
    }
    case Shape::Hexagon: {
        // Create bounding box around the circle/hexagon with padding
        QPoint center_ = (shape.startPoint + shape.endPoint) / 2;
        int radius = std::min(
            std::abs(shape.endPoint.x() - shape.startPoint.x()),
            std::abs(shape.endPoint.y() - shape.startPoint.y())
        ) / 2;
        return QRect(center_.x() - radius - SELECTION_PADDING,
                     center_.y() - radius - SELECTION_PADDING,
                     2 * radius + 2 * SELECTION_PADDING,
                     2 * radius + 2 * SELECTION_PADDING);
    }

    case Shape::Line: {
        // Create bounding box around the line with padding
        int lineThickness = brushSize_ / 2 + SELECTION_PADDING;
        return QRect(shape.startPoint, shape.endPoint)
                .normalized()
                .adjusted(-lineThickness, -lineThickness, 
                         lineThickness, lineThickness);
    }

    case Shape::Freehand: {
        // Create bounding box around all freehand points with padding
        if (shape.points.isEmpty())
            return QRect();

        int minX = shape.points[0].x();
        int minY = shape.points[0].y();
        int maxX = minX;
        int maxY = minY;

        for (const QPoint& pt : shape.points) {
            minX = std::min(minX, pt.x());
            minY = std::min(minY, pt.y());
            maxX = std::max(maxX, pt.x());
            maxY = std::max(maxY, pt.y());
        }

        int freehandPadding = brushSize_ / 2 + SELECTION_PADDING;
        return QRect(QPoint(minX, minY), QPoint(maxX, maxY))
                .adjusted(-freehandPadding, -freehandPadding, 
                         freehandPadding, freehandPadding);
    }

    case Shape::Text: {
        // Create bounding box around the text with padding
        QFontMetrics fm(shape.font);
        QRect r = fm.boundingRect(shape.text);
        r.moveTopLeft(shape.startPoint);
        return r.adjusted(-SELECTION_PADDING, -SELECTION_PADDING, 
                         SELECTION_PADDING, SELECTION_PADDING);
    }
    }

    return QRect();
}
