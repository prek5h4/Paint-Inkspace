#include "CanvasWidget.h"
#include "../Commands/ClipboardCommands.h"
#include <QDebug>


// Deep copy helper for Shape
std::shared_ptr<Shape> deepCopyShape(const Shape& original) {
    auto copy = std::make_shared<Shape>(
        original.type,
        original.startPoint,
        original.brush_color,
        original.width,
        original.fillColor
    );
    
    copy->endPoint = original.endPoint;
    copy->radius = original.radius;
    copy->text = original.text;
    copy->font = original.font;
    copy->points = original.points;
    
    return copy;
}

void CanvasWidget::cutShape() {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) {
        qDebug() << "No shape selected for cut";
        return;
    }
    
    // Deep copy the shape to clipboard
    clipboard_ = deepCopyShape(*shapes_[selectedShapeIndex_]);
    
    // Store the center point for smart paste positioning
    QRect boundingRect = selectShape(*shapes_[selectedShapeIndex_]);
    clipboardOffset_ = boundingRect.center();
    
    // Execute cut command (removes from canvas with undo support)
    std::shared_ptr<Shape> shapeToRemove = shapes_[selectedShapeIndex_];
    int index = selectedShapeIndex_;
    
    commandManager_.executeCommand(
        std::make_unique<CutShapeCommand>(this, shapeToRemove, index)
    );
    
    selectedShapeIndex_ = -1;
    update();
    
    qDebug() << "Shape cut to clipboard";
}

void CanvasWidget::copyShape() {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) {
        qDebug() << "No shape selected for copy";
        return;
    }
    
    // Deep copy the shape to clipboard
    clipboard_ = deepCopyShape(*shapes_[selectedShapeIndex_]);
    
    // Store the center point for smart paste positioning
    QRect boundingRect = selectShape(*shapes_[selectedShapeIndex_]);
    clipboardOffset_ = boundingRect.center();
    
    qDebug() << "Shape copied to clipboard";
}

void CanvasWidget::pasteShapeAtCursor(const QPoint& cursorPos) {
    if (!clipboard_) {
        qDebug() << "Clipboard is empty";
        return;
    }
    
    // Create a new copy of the clipboard shape
    auto newShape = deepCopyShape(*clipboard_);
    
    // Calculate the original shape's center
    QRect originalBounds = selectShape(*clipboard_);
    QPoint originalCenter_ = originalBounds.center();
    
    // Calculate offset to position at cursor
    QPoint offset = cursorPos - originalCenter_;
    
    // Apply offset to the new shape
    switch (newShape->type) {
        case Shape::Freehand:
            for (QPoint& pt : newShape->points) {
                pt += offset;
            }
            newShape->startPoint += offset;
            newShape->endPoint += offset;
            break;
            
        case Shape::Text:
            newShape->startPoint += offset;
            newShape->endPoint += offset;
            break;
            
        default:
            newShape->startPoint += offset;
            newShape->endPoint += offset;
            break;
    }
    
    // Execute paste command
    commandManager_.executeCommand(
        std::make_unique<PasteShapeCommand>(this, newShape)
    );
    
    update();
    
    qDebug() << "Shape pasted at cursor";
}