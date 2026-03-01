#include "BucketShapeCommand.h"
#include "../GUI/CanvasWidget.h"


BucketShapeCommand::BucketShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, const QColor& color)
    : canvas_(canvas), shape_(shape), newFillColor_(color)
{
    oldFillColor_ = shape_->fillColor;
}

void BucketShapeCommand::execute(){
    if (!canvas_ || !shape_) return;
    shape_->fillColor = newFillColor_;
    canvas_->update();   
}

void BucketShapeCommand::undo(){

    if (!canvas_ || !shape_) return;
    shape_->fillColor = oldFillColor_;
    canvas_->update();           
}
