#include "CanvasWidget.h"
#include <QRect>
#include <QPainter>
#include <QPainterPath>
#include <QColorDialog>
#include <QInputDialog>
//#include <iostream>
#include "../Commands/BucketShapeCommand.h"


void CanvasWidget::moveShape(QPoint& delta) {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) return;

    shapes_[selectedShapeIndex_]->startPoint += delta; //move the start and end points of the shape based on the mouse movement
    shapes_[selectedShapeIndex_]->endPoint += delta;

    if (shapes_[selectedShapeIndex_]->type == Shape::Freehand) {
        for (QPoint& pt : shapes_[selectedShapeIndex_]->points) {
            pt += delta;
        }
    }
    
    update();
}


void CanvasWidget::eraseShape() {
    for (int i = shapes_.size() - 1; i >= 0; --i) {
        if (selectShape(*shapes_[i]).contains(currentPoint_)) {
            std::shared_ptr<Shape> shapeToDelete = shapes_[i];
            commandManager_.executeCommand(
                std::make_unique<DeleteShapeCommand>(this, shapeToDelete) // Execute the delete command to remove the shape
            );
            break;
            
        }
    }
}

void CanvasWidget::bucketFill(const QPoint& position) {
    // Open color dialog to select replacement color
    QColor color = QColorDialog::getColor(replacementColor_, this, tr("Select Fill Color"));
    if (!color.isValid()) {
        return;
    }
        
    replacementColor_ = color;
        
    // Find the shape to fill
    for (auto& shape : shapes_) {
        if (selectShape(*shape).contains(position)) {
            // Use command pattern for undo/redo support
            commandManager_.executeCommand(std::make_unique<BucketShapeCommand>(this, shape, replacementColor_));
            break;
        }
    }
}    
