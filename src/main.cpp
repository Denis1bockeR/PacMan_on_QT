#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Map/map.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QGraphicsView view;
    Map* map = new Map("../Texture/map.txt", 50, 50, 20 ,20);
    view.setScene(map);
    view.show();
    return app.exec();
}