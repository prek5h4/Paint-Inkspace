#include "MoveShapeCommand.h"
#include "../GUI/CanvasWidget.h"
//#include <iostream>

MoveShapeCommand::MoveShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, QPoint delta)
    : canvas_(canvas), shape_(shape), delta(delta) {

    }
    void MoveShapeCommand::execute() {
        // Add delta to move forward
        shape_->startPoint += delta;
        shape_->endPoint += delta;
        
        if (shape_->type == Shape::Freehand) {
            for (QPoint& pt : shape_->points) {
                pt += delta;
            }
        }
        canvas_->update();
    }

    void MoveShapeCommand::undo() {
        // Subtract delta to move back
        shape_->startPoint -= delta;
        shape_->endPoint -= delta;
        
        if (shape_->type == Shape::Freehand) {
            for (QPoint& pt : shape_->points) {
                pt -= delta;
            }
        }
        canvas_->update();
    }

