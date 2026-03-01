#include "ToolMenu.h"
#include "CanvasWidget.h"

ToolMenu::ToolMenu(QMainWindow* mainWindow, CanvasWidget* canvas)
    : QObject(mainWindow), canvas(canvas), mainWindow(mainWindow)
{
    createActions();
    createToolbars();
}

void ToolMenu::createActions()
{
    // Rectangle Tool
    rectToolAction = new QAction(QIcon(":/icons/rectangle.png"), ToolMenu::tr("Rectangle Tool"), this);
    connect(rectToolAction, &QAction::triggered, this, &ToolMenu::selectRectTool);
    // Rounded Rectangle Tool
    roundedRectToolAction = new QAction(QIcon(":/icons/RoundedRect.png"), ToolMenu::tr("Rounded Rectangle Tool"), this);
    connect(roundedRectToolAction, &QAction::triggered, this, &ToolMenu::selectRoundedRectTool);
    // Circle Tool
    circleToolAction = new QAction(QIcon(":/icons/circle.png"), ToolMenu::tr("Circle Tool"), this);
    connect(circleToolAction, &QAction::triggered, this, &ToolMenu::selectCircleTool);
    // Line Tool
    lineToolAction = new QAction(QIcon(":/icons/line.png"), ToolMenu::tr("Line Tool"), this);
    connect(lineToolAction, &QAction::triggered, this, &ToolMenu::selectLineTool);
    // Hexagon Tool
    hexagonToolAction = new QAction(QIcon(":/icons/hexagon.png"), ToolMenu::tr("Hexagon Tool"), this);
    connect(hexagonToolAction, &QAction::triggered, this, &ToolMenu::selectHexagonTool);
    // Freehand Tool
    freehandToolAction = new QAction(QIcon(":/icons/freehand.png"), ToolMenu::tr("Freehand Tool"), this);
    connect(freehandToolAction, &QAction::triggered, this, &ToolMenu::selectFreehandTool);
    // Erase Tool
    eraseToolAction = new QAction(QIcon(":/icons/eraser.png"), ToolMenu::tr("Erase Tool"), this);
    connect(eraseToolAction, &QAction::triggered, this, &ToolMenu::selectEraseTool);
    // Move Tool
    moveToolAction = new QAction(QIcon(":/icons/move.png"), ToolMenu::tr("Move Tool"), this);
    connect(moveToolAction, &QAction::triggered, this, &ToolMenu::selectMoveTool);
    // Bucket Tool
    bucketToolAction = new QAction(QIcon(":/icons/bucket.png"), ToolMenu::tr("Bucket Tool"), this);
    connect(bucketToolAction, &QAction::triggered, this, &ToolMenu::selectBucketTool);
    // Stroke Color Action
    StrokeColorAction = new QAction(QIcon(":/icons/strokechange.png"), ToolMenu::tr("Stroke Color"), this);
    connect(StrokeColorAction, &QAction::triggered, this, &ToolMenu::selectStrokeColor);
    // Resize Tool
    resizeAction = new QAction(QIcon(":/icons/resize.png"), ToolMenu::tr("Resize Tool"), this);
    connect(resizeAction, &QAction::triggered, this, &ToolMenu::selectResizeTool);
    // Stroke Resize Action
    StrokeResizeAction = new QAction(QIcon(":/icons/strokesize.png"), ToolMenu::tr("Stroke Resize"), this);
    connect(StrokeResizeAction, &QAction::triggered, this, &ToolMenu::selectStrokeResize);
}

void ToolMenu::createToolbars()
{
    fileToolBar = mainWindow->addToolBar(ToolMenu::tr("Drawing Tools"));
    fileToolBar->addAction(rectToolAction);
    fileToolBar->addAction(roundedRectToolAction);
    fileToolBar->addAction(circleToolAction);
    fileToolBar->addAction(lineToolAction);
    fileToolBar->addAction(hexagonToolAction);
    fileToolBar->addAction(freehandToolAction);
    fileToolBar->addAction(eraseToolAction);
    fileToolBar->addAction(moveToolAction);
    fileToolBar->addAction(bucketToolAction);
    fileToolBar->addAction(StrokeColorAction);
    fileToolBar->addAction(StrokeResizeAction);
    fileToolBar->addAction(resizeAction);
}

void ToolMenu::selectRectTool()
{
    canvas->setTool(CanvasWidget::Tool::RectangleTool);
}
void ToolMenu::selectCircleTool()
{
    canvas->setTool(CanvasWidget::Tool::CircleTool);
}
void ToolMenu::selectLineTool()
{
    canvas->setTool(CanvasWidget::Tool::LineTool);
}
void ToolMenu::selectHexagonTool()
{
    canvas->setTool(CanvasWidget::Tool::HexagonTool);
}
void ToolMenu::selectFreehandTool()
{
    canvas->setTool(CanvasWidget::Tool::FreehandTool);
}
void ToolMenu::selectEraseTool()
{
    canvas->setTool(CanvasWidget::Tool::EraseTool);
}
void ToolMenu::selectMoveTool()
{
    canvas->setTool(CanvasWidget::Tool::MoveTool);
}
void ToolMenu::selectBucketTool()
{
    canvas->setTool(CanvasWidget::Tool::BucketTool); 
}
void ToolMenu::selectRoundedRectTool()
{
    canvas->setTool(CanvasWidget::Tool::RoundedRectangleTool); 
}
void ToolMenu::selectStrokeColor()
{
    canvas->setTool(CanvasWidget::Tool::StrokeColor);
}
void ToolMenu::selectResizeTool()
{
    canvas->setTool(CanvasWidget::Tool::ResizeTool);
}
void ToolMenu::selectStrokeResize()
{
    canvas->setTool(CanvasWidget::Tool::StrokeResize);
}