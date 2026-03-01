#include "DrawShapeCommand.h"
#include "../GUI/CanvasWidget.h"
//#include <iostream>

DrawShapeCommand::DrawShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape)
    : canvas_(canvas), shape_(shape), ownsShape_(true) {
    //std::cout << "DrawShapeCommand created: " << shape << std::endl;
}

DrawShapeCommand::~DrawShapeCommand() {
    // Only delete if we own it (shape was undone and not on canvas)
    if (ownsShape_ && shape_) {
        shape_.reset();
    }
}

void DrawShapeCommand::execute()
{
    if (!canvas_ || !shape_) {
        return;
    }
    canvas_->addShape(shape_);
    ownsShape_ = false;  // Canvas now owns the shape
    canvas_->update();
    //std::cout << "DrawShapeCommand::execute complete " << std::endl;
}

void DrawShapeCommand::undo()
{
    if (!canvas_ || !shape_) {
        return;
    }
    canvas_->removeShape(shape_);
    ownsShape_ = true;  // We now own the shape since it's off the canvas
    canvas_->update();
    //std::cout << "DrawShapeCommand::undo complete " << std::endl;
}
