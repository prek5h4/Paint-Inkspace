#include "ChangeStrokeColor.h"
#include "../GUI/CanvasWidget.h"


ChangeStrokeCommand::ChangeStrokeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, const QColor& color)
    : canvas_(canvas), shape_(shape), newStrokeColor_(color)
{
    oldStrokeColor_ = shape_->brush_color;
}

void ChangeStrokeCommand::execute(){
    if (!canvas_ || !shape_) return;
    shape_->brush_color = newStrokeColor_;
    canvas_->update();   
}

void ChangeStrokeCommand::undo(){

    if (!canvas_ || !shape_) return;
    shape_->brush_color = oldStrokeColor_;
    canvas_->update();           
}
