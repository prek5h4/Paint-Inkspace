#pragma once

#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>
#include "CanvasWidget.h"

class CanvasWidget;

class ToolMenu : public QObject {
    Q_OBJECT
    
public:
    ToolMenu(QMainWindow* mainWindow, CanvasWidget* canvas);
    ~ToolMenu() = default;

private:
    void createToolbars();
    void createActions();
    
    // UI Elements
    CanvasWidget* canvas;
    QMainWindow* mainWindow;
    QToolBar* fileToolBar;
    
    // Actions
    QAction* rectToolAction;
    QAction* roundedRectToolAction;
    QAction* circleToolAction;
    QAction* lineToolAction;
    QAction* hexagonToolAction;
    QAction* freehandToolAction;
    QAction* eraseToolAction;
    QAction* moveToolAction;
    QAction* bucketToolAction;
    QAction* StrokeColorAction;
    QAction* StrokeResizeAction;
    QAction* resizeAction;

private slots:
    void selectRectTool();
    void selectCircleTool();
    void selectLineTool();
    void selectHexagonTool();
    void selectFreehandTool();
    void selectEraseTool();
    void selectMoveTool();
    void selectBucketTool();
    void selectRoundedRectTool();
    void selectStrokeColor();
    void selectResizeTool();
    void selectStrokeResize();
};