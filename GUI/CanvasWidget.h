#pragma once
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QPoint>
#include <QRect>
#include <QInputDialog>
#include <vector>
#include <memory>
#include "../Parser/SVGDocument.h"
#include "../Parser/SVGElement.h"
#include "../History/CommandManager.h"
#include "../Commands/DrawShapeCommand.h"
#include "../Commands/DeleteShapeCommand.h"
#include "../Commands/MoveShapeCommand.h"


struct Shape {
    enum Type { Rectangle, Circle, Line, Hexagon, Freehand, Text };
    Type type;
    QPoint startPoint;
    QPoint endPoint;
    QVector<QPoint> points; // For freehand drawing
    QColor brush_color;
    int width;
    QColor fillColor;
    QString text;
    QFont font;
    int radius; // For rounded rectangles
    

    Shape() = default;

    Shape(Type t, QPoint start, QColor c, int w, QColor fill)
        : type(t), startPoint(start), endPoint(start), brush_color(c), width(w), fillColor(fill), radius(0) {}
};

class CanvasWidget : public QWidget {
    Q_OBJECT
public:
    enum Tool { None, RectangleTool, CircleTool, LineTool, HexagonTool, FreehandTool, TextTool, EraseTool, MoveTool, BucketTool, 
        RoundedRectangleTool, ResizeTool, StrokeColor, StrokeResize };
    
    explicit CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget() override;
    void newFile();
    void setTool(Tool t);
    void setBrushColor(const QColor& color);
    void setBrushSize(int width);
    void setFillColor(const QColor& color);
    void setFont(const QFont& font);
    void bucketFill(const QPoint& position);
    void clearCanvas();
    void changeStroke(const QPoint& position);
    void strokeResize(const QPoint& position);
    void cutShape();
    void copyShape();
    void pasteShapeAtCursor(const QPoint& position);
    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(std::shared_ptr<Shape> shape);
    void insertShape(int index, std::shared_ptr<Shape> shape);
    void moveShape(QPoint& delta);
    std::vector<std::shared_ptr<Shape>>& getShapes();
    void resizeShape(const QPoint& delta);
    // ADDED: Getter for shapes count
    size_t getShapesCount() const { return shapes_.size(); }
    
    CommandManager& getCommandManager() { return commandManager_; }
    
    SVGDocument getSVGDocument() const;
    void loadSVGDocument(const SVGDocument& doc);
    
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    
private:
    void drawShape(QPainter& painter, const Shape& shape);
    void drawHexagon(QPainter& painter, const QPoint& center, int radius);
    void writeTextAt(const QPoint& position, const QFont& font, const QColor& color, int brushSize);
    void eraseShape();
    QRect selectShape(const Shape& shape) const;
    
    QPoint startPoint_;
    QPoint currentPoint_;
    QColor replacementColor_;
    bool resize_;
    bool drawing_;
    bool eraser_;
    bool isDragging_;
    int selectedShapeIndex_;
    Tool currentTool_;
    QFont text_font_;
    std::vector<std::shared_ptr<Shape>> shapes_;
    std::shared_ptr<Shape> currentShape_;
    QColor brushColor_;
    QColor fillColor_;
    int brushSize_;
    CommandManager commandManager_;
    QPoint totalMoveDelta_;
    QPoint originalStartPoint_;
    QPoint originalEndPoint_;
    QPoint finalStartPoint_;
    QPoint finalEndPoint_;
    std::shared_ptr<Shape> clipboard_;  
    QPoint clipboardOffset_;
};
