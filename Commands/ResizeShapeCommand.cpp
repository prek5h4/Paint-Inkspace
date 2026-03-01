#include "ResizeShapeCommand.h"
#include "../GUI/CanvasWidget.h"

ResizeShapeCommand::ResizeShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, QPoint originalStartPoint, QPoint finalStartPoint, QPoint originalEndPoint, QPoint finalEndPoint)
    : canvas_(canvas), shape_(shape), originalStartPoint_(originalStartPoint), finalStartPoint_(finalStartPoint), originalEndPoint_(originalEndPoint), finalEndPoint_(finalEndPoint) {
    
}

void ResizeShapeCommand::execute(){
    
    if (!canvas_ || !shape_) return;

    shape_->startPoint = finalStartPoint_;
    shape_->endPoint = finalEndPoint_;
    //qDebug() << "Execute Resize: startPoint" << shape_->startPoint << "endPoint" << shape_->endPoint;
    canvas_->update();
}

void ResizeShapeCommand::undo(){
    
    if (!canvas_ || !shape_) return;
    shape_->startPoint = originalStartPoint_;
    shape_->endPoint = originalEndPoint_;
    //qDebug() << "Undo Resize: startPoint" << shape_->startPoint << "endPoint" << shape_->endPoint;
    canvas_->update();
}


