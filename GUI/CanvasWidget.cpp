#include "CanvasWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QInputDialog>
#include <cmath>
#include <QDebug>
//#include <iostream>
CanvasWidget::CanvasWidget(QWidget* parent)
    : QWidget(parent),
      drawing_(false),
      currentTool_(None),
      brushColor_(Qt::black),
      brushSize_(2),
      fillColor_(Qt::white),
      text_font_(QFont("Arial", 12)),
      isDragging_(false),
      selectedShapeIndex_(-1),
      currentShape_(nullptr),
      eraser_(false),
      resize_(false)
{
    setMouseTracking(false);
    setMinimumSize(400, 300);
}
CanvasWidget::~CanvasWidget() {
    commandManager_.clear();
    
    shapes_.clear();

    currentShape_ = nullptr;
}
void CanvasWidget::setTool(Tool t) { currentTool_ = t; }
void CanvasWidget::setBrushColor(const QColor& color) { brushColor_ = color; }
void CanvasWidget::setFont(const QFont& font) { text_font_ = font; }
void CanvasWidget::setBrushSize(int width) { brushSize_ = width; }
void CanvasWidget::setFillColor(const QColor& color) { fillColor_ = color; }

void CanvasWidget::clearCanvas() {
    shapes_.clear();
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton || currentTool_ == None)
        return;
    
    if(currentTool_ == MoveTool){
        for (int i = shapes_.size() - 1; i >= 0; --i) {
            QRect shapeRect = selectShape(*shapes_[i]);
            if (shapeRect.contains(event->pos())) {
                selectedShapeIndex_ = i;
                isDragging_ = true;
                currentPoint_ = event->pos();
                totalMoveDelta_ = QPoint(0, 0);  // Reset total movement
                //std::cout << "Starting drag" << std::endl;
                return;  
            }
        }
        return;  
    }

    drawing_ = true;
    startPoint_ = event->pos();
    currentPoint_ = startPoint_;

    if (currentTool_ == EraseTool) {
        drawing_ = false;
        eraser_ = true;
        eraseShape();  
        return;
    }
    if (currentTool_ == ResizeTool) {
        resize_ = true;
        drawing_ = false; 
        for (int i = shapes_.size() - 1; i >= 0; --i) {  
            QRect shapeRect = selectShape(*shapes_[i]);
            if (shapeRect.contains(event->pos())) {
                selectedShapeIndex_ = i; 
                //std::cout<<"Selected shape index for resizing: " << selectedShapeIndex << std::endl;
                currentPoint_ = event->pos();
                
                originalStartPoint_ = shapes_[selectedShapeIndex_]->startPoint; // Store original start point before resizing
                originalEndPoint_ = shapes_[selectedShapeIndex_]->endPoint;    // Store original end point before resizing
                
                return;  
            }
        }
        return;
    }

    switch (currentTool_) {
        //qDebug() << "Switch entered with currentTool:" << currentTool_;
    case RectangleTool:
        currentShape_ = std::make_shared<Shape>(Shape::Rectangle, startPoint_, brushColor_, brushSize_, fillColor_);
        //qDebug() << "Created shape with type:" << currentShape_->type;
        break;
    
    case RoundedRectangleTool:
        currentShape_ = std::make_shared<Shape>(Shape::Rectangle, startPoint_, brushColor_, brushSize_, fillColor_);
        currentShape_->radius = 0; // Default radius, can be changed on mouse release
        break;

    case CircleTool:
        currentShape_ = std::make_shared<Shape>(Shape::Circle, startPoint_, brushColor_, brushSize_, fillColor_);
        //qDebug() << "Created shape with type:" << currentShape_ ->type;
        break;

    case LineTool:
        currentShape_ = std::make_shared<Shape>(Shape::Line, startPoint_, brushColor_, brushSize_, fillColor_);
        break;

    case HexagonTool:
        currentShape_ = std::make_shared<Shape>(Shape::Hexagon, startPoint_, brushColor_, brushSize_, fillColor_);
        break;

    case FreehandTool:
        currentShape_ = std::make_shared<Shape>(Shape::Freehand, startPoint_, brushColor_, brushSize_, fillColor_);
        currentShape_->points.append(startPoint_);
        //std::cout<<"freehand"<<std::endl;
        break;

    case TextTool:
        currentShape_ = std::make_shared<Shape>(Shape::Text, startPoint_, brushColor_, brushSize_, fillColor_);
        currentShape_->font = text_font_;
        break;

    case EraseTool:
        drawing_ = false;
        eraser_ = true;
        eraseShape(); // Call eraseShape to handle erasing logic
        return;
    case BucketTool:
        bucketFill(event->pos()); // Call bucketFill to handle fill logic
        drawing_ = false;
        return;
    case StrokeColor:
        changeStroke(event->pos()); // Call changeStroke to handle stroke color change logic
        drawing_ = false;
        return;
    case StrokeResize:
        strokeResize(event->pos()); // Call strokeResize to handle stroke size change logic
        drawing_ = false;
        return;
    default:
        break;
    }
    
}

