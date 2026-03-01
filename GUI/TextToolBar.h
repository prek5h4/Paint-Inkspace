#pragma once

#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QToolButton>
#include "CanvasWidget.h"

class CanvasWidget;

class TextToolBar : public QObject {
    Q_OBJECT
public:
    TextToolBar(QMainWindow* mainWindow, CanvasWidget* canvas);
    ~TextToolBar() = default;
    
    QToolBar* getToolBar() { return textToolBar; }
    
private:
    void createToolbars();
    void createActions();
    
    // UI Elements
    CanvasWidget* canvas;
    QMainWindow* mainWindow;
    QToolBar* textToolBar;
    
    // Actions
    QAction* textToolAction;
    QAction* selectFontAction;

    
    // Dropdown menu for text settings
    QMenu* textSettingsMenu;
    QToolButton* textSettingsButton;

private slots:
    void selectTextTool();
    void selectFont();

};
