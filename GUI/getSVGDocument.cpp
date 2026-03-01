#include "CanvasWidget.h"

SVGDocument CanvasWidget::getSVGDocument() const {
    SVGDocument doc(width(), height());  // Use canvas dimensions

    // Convert each Shape to SVGElement
    for (const auto& shape : shapes_) {
        if (!shape) continue;

        std::shared_ptr<SVGElement> element;

        switch (shape->type) {
        case Shape::Rectangle: {
            element = std::make_shared<SVGRectangle>( 
                //get the top-left corner and dimensions from startPoint and endPoint
                shape->startPoint.x(),
                shape->startPoint.y(),
                shape->endPoint.x() - shape->startPoint.x(),
                shape->endPoint.y() - shape->startPoint.y(),
                shape->fillColor.name(),
                shape->brush_color.name(),
                shape->width
                );
            break;
        }

        case Shape::Circle: {
            // Calculate center and radius from bounding box
            double cx = (shape->startPoint.x() + shape->endPoint.x()) / 2.0;
            double cy = (shape->startPoint.y() + shape->endPoint.y()) / 2.0;
            double r = std::min(
                           std::abs(shape->endPoint.x() - shape->startPoint.x()),
                           std::abs(shape->endPoint.y() - shape->startPoint.y())
                           ) / 2.0;

            element = std::make_shared<SVGCircle>(cx, cy, r, shape->fillColor.name(), shape->brush_color.name(), shape->width);
            
            break;
        }

        case Shape::Line: {
            element = std::make_shared<SVGLine>(
                shape->startPoint.x(),
                shape->startPoint.y(),
                shape->endPoint.x(),
                shape->endPoint.y(),
                shape->brush_color.name(),
                shape->width
                );
            break;
        }

        case Shape::Hexagon: {
            // Calculate center and side length from bounding box
            double cx = (shape->startPoint.x() + shape->endPoint.x()) / 2.0;
            double cy = (shape->startPoint.y() + shape->endPoint.y()) / 2.0;
            double sl = std::min(
                            std::abs(shape->endPoint.x() - shape->startPoint.x()),
                            std::abs(shape->endPoint.y() - shape->startPoint.y())
                            ) / 2.0;

            element = std::make_shared<SVGHexagon>(cx, cy, sl, shape->fillColor.name(), shape->brush_color.name(), shape->width);
            break;
        }

        case Shape::Freehand: {
            // Convert QVector<QPoint> to vector<pair<double,double>>
            std::vector<std::pair<double, double>> points;
            for (const QPoint& pt : shape->points) {
                points.push_back({static_cast<double>(pt.x()),
                                  static_cast<double>(pt.y())});
            }

            element = std::make_shared<SVGFreehand>(
                points,
                shape->brush_color.name(),
                shape->width
                );
            break;
        }

        case Shape::Text: {
            element = std::make_shared<SVGText>(
                shape->startPoint.x(),
                shape->startPoint.y(),
                shape->text,
                shape->brush_color.name(),
                shape->font.family(),
                shape->font.pointSize()
                );
            break;
        }

        default:
            continue;
        }

        if (element) {
            doc.addElement(element);
        }
    }

    return doc;
}
