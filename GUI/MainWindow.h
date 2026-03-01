#pragma once
#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QObject>

#include <QColor>
#include <QPoint>
#include <QToolButton>
#include <memory>
#include <QIcon>
#include <QMenu>
#include <QMainWindow>
#include "CanvasWidget.h"
#include "ToolMenu.h"
#include "TextToolBar.h"
#include "../Parser/SVGParser.h"
#include "../Parser/SvgWriter.h"
#include "../Parser/SVGDocument.h"
#include "../Parser/XmlTokenizer.h"
#include "../History/CommandManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
    ToolMenu* toolMenu;
    TextToolBar* textToolBar;
    
private:
    void createMenus();
    void createToolbars();
    void createActions();
    
    // UI Elements
    CanvasWidget* canvas;
    QMenu* fileMenu;
    QToolBar* fileToolBar;
    
    // Actions
    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* exitAction;
    QAction* brushColorAction;
    QAction* brushSizeAction;
    QAction* fillColorAction;
    QAction* UndoAction;
    QAction* RedoAction;
    QAction* CutAction;
    QAction* CopyAction;
    QAction* PasteAction;
     
    // Dropdown menu for brush/fill settings
    QMenu* brushSettingsMenu;
    QToolButton* brushSettingsButton;

    // Drawing state
    bool drawing;
    QColor brushColor;
    QColor fillColor;
    int brushSize;
    QString currentFilename;

private slots:
    void openNewFile();
    void openFile();
    void saveFile();
    void changeBrushColor();
    void changeBrushSize();
    void changeFillColor();
    void undo();
    void redo();
    void choosecutShape();
    void choosecopyShape();
    void choosepasteShapeAtCursor();
};


