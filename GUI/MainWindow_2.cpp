#include "MainWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>

void MainWindow::undo(){
    canvas->getCommandManager().undo();
    canvas->update();
}

void MainWindow::redo(){
    canvas->getCommandManager().redo();
    canvas->update();
}

void MainWindow::choosecutShape() {
    canvas->cutShape();
}

void MainWindow::choosecopyShape() {
    canvas->copyShape();
}

void MainWindow::choosepasteShapeAtCursor() {
    // Get current cursor position relative to canvas
    QPoint cursorPos = canvas->mapFromGlobal(QCursor::pos());
    canvas->pasteShapeAtCursor(cursorPos);
}

void MainWindow::openNewFile() 
{
    canvas->newFile();  
    setWindowTitle("Paint");
    //statusBar()->showMessage("New file created", 2000);
}

