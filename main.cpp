#include <QApplication>
#include "GUI/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.setWindowTitle("Paint");
    window.resize(1000, 700);
    window.show();
    
    return app.exec();
}
