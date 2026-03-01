#pragma once
#include "Command.h"
#include <QPoint>


class CanvasWidget;
struct Shape;


class ResizeShapeCommand : public Command {
public:
    ResizeShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, QPoint originalStartPoint, QPoint finalStartPoint, QPoint originalEndPoint, QPoint finalEndPoint);
    void execute() override;   // moves shape
    void undo() override;      // removes same shape

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    QPoint originalStartPoint_;
    QPoint finalStartPoint_;
    QPoint originalEndPoint_;
    QPoint finalEndPoint_;
};
