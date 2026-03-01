#include "CanvasWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QInputDialog>
#include <cmath>
//#include <iostream>
#include <QDebug>
#include "../Commands/MoveShapeCommand.h"
#include "../Commands/ResizeShapeCommand.h"
#include "../Commands/ChangeStrokeColor.h"

void CanvasWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (resize_ && selectedShapeIndex_ != -1) {
        //std::cout<<"resizing" << std::endl;
        QPoint newPoint = event->pos();
        QPoint delta = newPoint - currentPoint_;

        resizeShape(delta);  //calculate the new end point based on the mouse movement

        currentPoint_ = newPoint;
        return;
    }
    if (isDragging_ && selectedShapeIndex_ != -1) {
        QPoint delta = event->pos() - currentPoint_;
        totalMoveDelta_ += delta;  // Accumulate total movement during drag
        moveShape(delta); // Move the shape based on the mouse movement
        currentPoint_ = event->pos();
        update();
        return;
    }
    if (!currentShape_){
        return;
    }
    if (currentTool_ == FreehandTool) {
        
        currentShape_->points.append(event->pos()); // Add points to the freehand shape as the mouse moves
    }
   
    else {
        if(currentTool_ != EraseTool && currentTool_!= ResizeTool ) currentShape_->endPoint = event->pos();
    }
    update();
    
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent* event)
{
    //std::cout << "mouseReleaseEvent call" << std::endl;
    if (event->button() != Qt::LeftButton)
        return;
    if (resize_) {
        finalStartPoint_ = shapes_[selectedShapeIndex_]->startPoint; // Get the final start point after resizing
        finalEndPoint_ = shapes_[selectedShapeIndex_]->endPoint; // Get the final end point after resizing
        
        if (originalStartPoint_ != finalStartPoint_ || originalEndPoint_ != finalEndPoint_) {
            commandManager_.executeCommand(
                std::make_unique<ResizeShapeCommand>(
                    this, 
                    shapes_[selectedShapeIndex_], originalStartPoint_, finalStartPoint_, originalEndPoint_, finalEndPoint_
                )
            );
        }
        //std::cout<<"Finished resizing shape index: " << selectedShapeIndex << std::endl;
        resize_ = false;
        selectedShapeIndex_ = -1;
        currentShape_ = nullptr;
        update();
        return;
    }
    if (isDragging_) {
        if (selectedShapeIndex_ >= 0 && selectedShapeIndex_ < shapes_.size() && 
            (totalMoveDelta_.x() != 0 || totalMoveDelta_.y() != 0)) {
            //for move tool we use command without execute as shape is already moved
            commandManager_.addCommandWithoutExecute(
                std::make_unique<MoveShapeCommand>(
                    this, 
                    shapes_[selectedShapeIndex_], 
                    totalMoveDelta_  // How much it moved
                )
            );
        }
        isDragging_ = false;
        //selectedShapeIndex_ = -1;
        totalMoveDelta_ = QPoint(0, 0);  // Reset for next drag
        update();
        return;
    }
    if (currentTool_ == BucketTool) {
        drawing_ = false; 
        currentShape_ = nullptr;
        update();
        return;
    }
    if (eraser_) {
        drawing_ = false;
        eraser_ = false;
        currentShape_ = nullptr;
        update();
        return;
    }
    if (currentTool_ == RoundedRectangleTool) {
        //open a dialog to ask for corner radius
        bool ok;
        int radius = QInputDialog::getInt(
            this, tr("Corner Radius"), tr("Enter corner radius:"), 
            10, 0, 100, 1, &ok
        );
        if (ok) {
            currentShape_->radius = radius;
        } else {
            currentShape_->radius = 0; // Default to sharp corners if cancelled
        }
    }
    if (!drawing_)
        return;
    
    drawing_ = false;
    
    if (!currentShape_) {
        return;
    }
    
    currentShape_->endPoint = event->pos();
    //get end point at final mouse release position

    if (currentTool_ == TextTool) {
        bool ok;
        QString text = QInputDialog::getText(
            this, tr("Input Text"), tr("Enter text:"),
            QLineEdit::Normal, "", &ok
        );

        if (ok && !text.isEmpty()) {
            currentShape_->text = text;
        } else {
            // User cancelled - delete the shape
            currentShape_ = nullptr;
            update();
            return;
        }
    }

    //qDebug() << "Tool:" << currentTool_ << "Shape type:" << currentShape_->type;
    commandManager_.executeCommand(std::make_unique<DrawShapeCommand>(this, currentShape_));
    //std::cout << "DrawShapeCommand executed" << std::endl;
    //qDebug() << "After add - Last shape type:" << shapes_.back()->type;
    currentShape_ = nullptr;  // Command now owns the shape
    
    update();
}
