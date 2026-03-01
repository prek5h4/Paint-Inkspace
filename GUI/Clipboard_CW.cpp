#include "CanvasWidget.h"
#include "../Commands/ClipboardCommands.h"


std::shared_ptr<Shape> deepCopyShape(const Shape& original) {
    auto copy = std::make_shared<Shape>(
        original.type, original.startPoint,
        original.brush_color, original.width, original.fillColor
    );
    //using deep copy to ensure clipboard shape is independent of original shape on canvas
    copy->endPoint = original.endPoint; 
    copy->radius = original.radius;
    copy->text = original.text;
    copy->font = original.font;
    copy->points = original.points;
    return copy;
}

void CanvasWidget::cutShape() {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) {
        return;
    }
    clipboard_ = deepCopyShape(*shapes_[selectedShapeIndex_]); // Deep copy the shape to clipboard

     // Store the center point for smart paste positioning
    std::shared_ptr<Shape> shapeToRemove = shapes_[selectedShapeIndex_];
    int index = selectedShapeIndex_;
    commandManager_.executeCommand(
        std::make_unique<CutShapeCommand>(this, shapeToRemove, index)
    );
    selectedShapeIndex_ = -1;
    update();
}

void CanvasWidget::copyShape() {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) {
        return;
    }
    // Deep copy the shape to clipboard to ensure it is independent of the original shape on canvas
    clipboard_ = deepCopyShape(*shapes_[selectedShapeIndex_]);
}

void CanvasWidget::pasteShapeAtCursor(const QPoint& cursorPos) {
    if (!clipboard_) return;
    
    auto newShape = deepCopyShape(*clipboard_);

    QRect originalBounds = selectShape(*clipboard_); // Get the bounding box of the original shape for calculating offset
    QPoint originalCenter = originalBounds.center(); //Get original centre 

    QPoint offset = cursorPos - originalCenter;

    if (newShape->type == Shape::Freehand) { // For freehand shapes, we need to offset all the points
        for (QPoint& pt : newShape->points) {
            pt += offset;
        }
    }
    newShape->startPoint += offset; // Offset the start and end points of the shape to position it at the cursor
    newShape->endPoint += offset;
    
    commandManager_.executeCommand(
        std::make_unique<PasteShapeCommand>(this, newShape)
    );
    
    update();
}
