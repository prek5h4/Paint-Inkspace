#include "CanvasWidget.h"
#include <memory>

void CanvasWidget::loadSVGDocument(const SVGDocument& doc) {
    // Clear existing shapes
    shapes_.clear();
    
    // Convert each SVGElement to Shape
    for (const auto& element : doc.getElements()) {
        if (!element) continue;
        
        auto shape = std::make_shared<Shape>();
        
        // Determine shape type and convert based on element type
        if (auto rect = std::dynamic_pointer_cast<SVGRectangle>(element)) {
            shape->type = Shape::Rectangle;
            shape->startPoint = QPoint(rect->getX(), rect->getY());
            shape->endPoint = QPoint(rect->getX() + rect->getWidth(),
                                     rect->getY() + rect->getHeight());
            shape->fillColor = QColor(rect->getFill());
            shape->brush_color = QColor(rect->getStroke());
            shape->width = rect->getStrokeWidth();
        }
        else if (auto circle = std::dynamic_pointer_cast<SVGCircle>(element)) {
            shape->type = Shape::Circle;
            // Reconstruct bounding box from center and radius
            int cx = circle->getCx();
            int cy = circle->getCy();
            int r = circle->getRadius();
            shape->startPoint = QPoint(cx - r, cy - r);
            shape->endPoint = QPoint(cx + r, cy + r);
            shape->fillColor = QColor(circle->getFill());
            shape->brush_color = QColor(circle->getStroke());
            shape->width = circle->getStrokeWidth();
        }
        else if (auto line = std::dynamic_pointer_cast<SVGLine>(element)) {
            shape->type = Shape::Line;
            shape->startPoint = QPoint(line->getX1(), line->getY1());
            shape->endPoint = QPoint(line->getX2(), line->getY2());
            shape->brush_color = QColor(line->getStroke());
            shape->width = line->getStrokeWidth();
        }
        else if (auto hexagon = std::dynamic_pointer_cast<SVGHexagon>(element)) {
            shape->type = Shape::Hexagon;
            // Reconstruct bounding box from center and side length
            int cx = hexagon->getCx();
            int cy = hexagon->getCy();
            int sl = hexagon->getSideLength();
            shape->startPoint = QPoint(cx - sl, cy - sl);
            shape->endPoint = QPoint(cx + sl, cy + sl);
            shape->fillColor = QColor(hexagon->getFill());
            shape->brush_color = QColor(hexagon->getStroke());
            shape->width = hexagon->getStrokeWidth();
        }
        else if (auto freehand = std::dynamic_pointer_cast<SVGFreehand>(element)) {
            shape->type = Shape::Freehand;
            shape->brush_color = QColor(freehand->getStroke());
            shape->width = freehand->getStrokeWidth();
            
            // Convert points from vector<pair<double,double>> to QVector<QPoint>
            const auto& svgPoints = freehand->getPoints();
            for (const auto& pt : svgPoints) {
                shape->points.append(QPoint(pt.first, pt.second));
            }
            
            // Set start and end points from first and last points
            if (!shape->points.isEmpty()) {
                shape->startPoint = shape->points.first();
                shape->endPoint = shape->points.last();
            }
        }
        else if (auto text = std::dynamic_pointer_cast<SVGText>(element)) {
            shape->type = Shape::Text;
            shape->startPoint = QPoint(text->getX(), text->getY());
            shape->text = text->getContent();
            shape->brush_color = QColor(text->getFill());
            
            // Set font
            shape->font.setFamily(text->getFontFamily());
            shape->font.setPointSize(text->getFontSize());
        }
        else {
            // Unknown element type, skip it
            continue;
        }
        
        shapes_.push_back(shape);
    }
    
    // Trigger repaint to display loaded shapes
    update();
}
