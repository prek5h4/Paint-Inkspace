#pragma once
#include "Command.h"
#include <QPoint>

class CanvasWidget;
struct Shape;

class ChangeStrokeSizeCommand : public Command {
public:
    ChangeStrokeSizeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, int size);
    void execute() override;   
    void undo() override;      

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    int newStrokeSize_;
    int oldStrokeSize_;
};
