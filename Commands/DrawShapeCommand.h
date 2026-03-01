#pragma once
#include "Command.h"

class CanvasWidget;
struct Shape;

class DrawShapeCommand : public Command {
private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    bool ownsShape_;  // Track if this command owns the shape memory

public:
    DrawShapeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape);
    ~DrawShapeCommand() override;
    
    void execute() override;
    void undo() override;
};