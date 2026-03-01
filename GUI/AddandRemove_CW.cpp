#include "CanvasWidget.h"
#include <algorithm>
#include <vector>
#include <QColorDialog>
#include "../Commands/ChangeStrokeColor.h"
#include "../Commands/ChangeStrokeSizeCommand.h"

void CanvasWidget::addShape(std::shared_ptr<Shape> shape) {
    shapes_.push_back(shape); //adds shape to the end of the vector
}
void CanvasWidget::removeShape(std::shared_ptr<Shape> shape) {
    auto it = std::find(shapes_.begin(), shapes_.end(), shape); //finds the shape in the vector

    if (it != shapes_.end()) {
        shapes_.erase(it); //removes the shape from the vector if found
    }
}

void CanvasWidget::insertShape(int index, std::shared_ptr<Shape> shape) {
    if (index >= 0 && index <= static_cast<int>(shapes_.size())) {
        shapes_.insert(shapes_.begin() + index, shape);
    }
}
std::vector<std::shared_ptr<Shape>>& CanvasWidget::getShapes(){
    return shapes_;
}

void CanvasWidget::changeStroke(const QPoint& position) {
    // Open color dialog to select replacement color
    QColor color = QColorDialog::getColor(replacementColor_, this, tr("Select Stroke Color"));
    if (!color.isValid()) {
        return;
    }
        
    replacementColor_ = color;
        
    // Find the shape to change strokecolor
    for (auto& shape : shapes_) {
        if (selectShape(*shape).contains(position)) {
            // Use command pattern for undo/redo support
            commandManager_.executeCommand(std::make_unique<ChangeStrokeCommand>(this, shape, replacementColor_));
            break;
        }
    }
}  

void CanvasWidget::resizeShape(const QPoint& delta) {
    if (selectedShapeIndex_ < 0 || selectedShapeIndex_ >= static_cast<int>(shapes_.size())) return;
    //qDebug() << "Before:" << shapes_[selectedShapeIndex_]->endPoint;
    shapes_[selectedShapeIndex_]->endPoint += delta;
    //qDebug() << "After:" << shapes_[selectedShapeIndex_]->endPoint;

    update();
}

void CanvasWidget::newFile() {
    shapes_.clear();
    commandManager_.clear();
    drawing_ = false;
    isDragging_ = false;
    resize_ = false;
    eraser_ = false;
    selectedShapeIndex_ = -1;
    totalMoveDelta_ = QPoint(0, 0);
    currentShape_ = nullptr;
    clipboard_ = nullptr;
    currentTool_ = None;
    // Reset colors and brush size to defaults
    brushColor_ = Qt::black;
    brushSize_ = 2;
    fillColor_ = Qt::white;
    update();
}

void CanvasWidget::strokeResize(const QPoint& position) {
    // Open input dialog to select new stroke size
    bool ok;
    int size = QInputDialog::getInt(
        this, tr("Brush Size"), tr("Enter Brush Size:"), 
        brushSize_, 1, 100, 1, &ok
    );
    if (ok) {
        for (auto& shape : shapes_) {
        if (selectShape(*shape).contains(position)) {
            // Use command pattern for undo/redo support
            commandManager_.executeCommand(std::make_unique<ChangeStrokeSizeCommand>(this, shape, size));
            break;
        }
    }
    }

}
