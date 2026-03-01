#include "MainWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QTextDocument>
#include <QToolButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      toolMenu(nullptr),
      textToolBar(nullptr),
      drawing(false),
      brushColor(Qt::black),
      fillColor(Qt::white),
      brushSize(2),
      brushSettingsMenu(nullptr),
      brushSettingsButton(nullptr)

{
    setWindowTitle("Paint");
    
    canvas = new CanvasWidget(this);
    setCentralWidget(canvas);
    resize(800, 600);
    
    // Set initial brush properties
    canvas->setBrushColor(brushColor);
    canvas->setBrushSize(brushSize);
    canvas->setFillColor(fillColor);
    
    createActions();
    createMenus();
    createToolbars();
    
    toolMenu = new ToolMenu(this, canvas);
    textToolBar = new TextToolBar(this, canvas);
}

void MainWindow::createActions()
{
    // New File
    newFileAction = new QAction(tr("&New"), this);
    newFileAction->setShortcut(QKeySequence::New);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::openNewFile);

    // Open File
    openFileAction = new QAction(tr("&Open"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    // Save File
    saveFileAction = new QAction(tr("&Save"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);

    // Exit
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    //Undo
    UndoAction = new QAction(tr("&Undo"), this);
    UndoAction->setShortcut(QKeySequence::Undo);
    connect(UndoAction, &QAction::triggered, this, &MainWindow::undo);

    //Redo
    RedoAction = new QAction(tr("&Redo"), this);
    RedoAction->setShortcut(QKeySequence::Redo);
    connect(RedoAction, &QAction::triggered, this, &MainWindow::redo);
    
    //Cut
    CutAction = new QAction(tr("&Cut"), this);
    CutAction->setShortcut(QKeySequence::Cut);
    connect(CutAction, &QAction::triggered, this, &MainWindow::choosecutShape);

    //Copy
    CopyAction = new QAction(tr("&Copy"), this);
    CopyAction->setShortcut(QKeySequence::Copy);
    connect(CopyAction, &QAction::triggered, this, &MainWindow::choosecopyShape);

    //Paste
    PasteAction = new QAction(tr("&Paste"), this);
    PasteAction->setShortcut(QKeySequence::Paste);
    connect(PasteAction, &QAction::triggered, this, &MainWindow::choosepasteShapeAtCursor);
    
    // Brush Color
    brushColorAction = new QAction(tr("Brush &Color"), this);
    connect(brushColorAction, &QAction::triggered, this, &MainWindow::changeBrushColor);

    // Brush Size
    brushSizeAction = new QAction(tr("Brush &Size"), this);
    connect(brushSizeAction, &QAction::triggered, this, &MainWindow::changeBrushSize);
    
    // Fill Color 
    fillColorAction = new QAction(tr("&Fill Color"), this);
    connect(fillColorAction, &QAction::triggered, this, &MainWindow::changeFillColor);
    
}

void MainWindow::createMenus() 
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    fileMenu = menuBar()->addMenu(tr("&Edit"));
    fileMenu->addAction(UndoAction);
    fileMenu->addAction(RedoAction);

    fileMenu = menuBar()->addMenu(tr("&Clipboard"));
    fileMenu->addAction(CutAction);
    fileMenu->addAction(CopyAction);
    fileMenu->addAction(PasteAction);
}




