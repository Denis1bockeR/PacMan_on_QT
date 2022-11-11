#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

#include "Window/mainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}