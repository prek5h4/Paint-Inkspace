#include "DeleteShapeCommand.h"
#include "../GUI/CanvasWidget.h"


DeleteShapeCommand::DeleteShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape)
    : canvas_(canvas), deletedShape_(shape), shapeIndex_(-1) {}

void DeleteShapeCommand::execute() {
    // Get the shapes vector from canvas
    auto& shapes = canvas_->getShapes();

    // Find the shape to delete
    auto it = std::find(shapes.begin(), shapes.end(), deletedShape_);

    if (it != shapes.end()) {
        shapeIndex_ = std::distance(shapes.begin(), it);
        canvas_->removeShape(deletedShape_);
    }
}

void DeleteShapeCommand::undo() {
    if (shapeIndex_ >= 0) {
        canvas_->insertShape(shapeIndex_, deletedShape_);
    }
}
