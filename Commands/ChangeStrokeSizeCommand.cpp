#include "ChangeStrokeSizeCommand.h"
#include "../GUI/CanvasWidget.h"


ChangeStrokeSizeCommand::ChangeStrokeSizeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, int size)
    : canvas_(canvas), shape_(shape), newStrokeSize_(size)
{
    oldStrokeSize_ = shape_->width;
}

void ChangeStrokeSizeCommand::execute(){
    if (!canvas_ || !shape_) return;
    shape_->width = newStrokeSize_;
    canvas_->update();   
}

void ChangeStrokeSizeCommand::undo(){

    if (!canvas_ || !shape_) return;
    shape_->width = oldStrokeSize_;
    canvas_->update();           
}
