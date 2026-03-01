#pragma once
#include "Command.h"
#include "../GUI/CanvasWidget.h"

class BucketShapeCommand : public Command {
public:
    BucketShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, const QColor& color);
    void execute() override;   
    void undo() override;      

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    QColor newFillColor_;
    QColor oldFillColor_;
};
