#pragma once
#include "Command.h"
#include <QColor>

class CanvasWidget;
struct Shape;

class ChangeStrokeCommand : public Command {
public:
    ChangeStrokeCommand(CanvasWidget* canvas, std::shared_ptr<Shape> shape, const QColor& color);
    void execute() override;   
    void undo() override;      

private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;
    QColor newStrokeColor_;
    QColor oldStrokeColor_;
};
