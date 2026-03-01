#pragma once
#include "Command.h"
#include <QPoint>

class CanvasWidget;
struct Shape;


class MoveShapeCommand : public Command {
public:
    MoveShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, QPoint delta);

    void execute() override;   // moves shape
    void undo() override;      // removes same shape

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    QPoint delta;
};
