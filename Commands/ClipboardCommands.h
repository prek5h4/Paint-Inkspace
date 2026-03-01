#pragma once
#include "Command.h"
#include "../GUI/CanvasWidget.h"
#include <memory>


class CutShapeCommand : public Command {
private:
    CanvasWidget* canva_;
    std::shared_ptr<Shape> shape_;
    int shapeIndex_;

public:
    CutShapeCommand(CanvasWidget* c, std::shared_ptr<Shape> s, int index)
        : canva_(c), shape_(s), shapeIndex_(index) {}

    void execute() override {
        // Remove from canvas
        canva_->removeShape(shape_);
        canva_->update();
    }

    void undo() override {
        // Restore to canvas at original position
        canva_->insertShape(shapeIndex_, shape_);
        canva_->update();
    }
};

// Command for Paste operation
class PasteShapeCommand : public Command {
private:
    CanvasWidget* canvas_;
    std::shared_ptr<Shape> shape_;

public:
    PasteShapeCommand(CanvasWidget* c, std::shared_ptr<Shape> s)
        : canvas_(c), shape_(s) {}

    void execute() override {
        canvas_->addShape(shape_);
        canvas_->update();
    }

    void undo() override {
        canvas_->removeShape(shape_);
        canvas_->update();
    }
};

