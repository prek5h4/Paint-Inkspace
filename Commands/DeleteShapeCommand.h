#pragma once
#include "Command.h"
#include <memory>
#include <vector>

class CanvasWidget;
struct Shape;  // Forward declaration

class DeleteShapeCommand : public Command {
public:
    DeleteShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape);

    void execute();
    void undo();

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> deletedShape_;
    int shapeIndex_;
};
