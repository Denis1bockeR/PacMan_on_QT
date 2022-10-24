#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Map/map.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QGraphicsView view;
    Map* map = new Map("../Texture/map.txt", 20 ,29);
    view.setScene(map);
    view.setBackgroundBrush(QBrush(Qt::black));
    view.show();
    return app.exec();
}