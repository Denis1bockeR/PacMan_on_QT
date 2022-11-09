#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "game.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QGraphicsView view;
    Game* game = new Game("../Texture/map.txt", 20, 29);
    view.setScene(game->getMap());
    view.setBackgroundBrush(QBrush(Qt::black));
    view.show();
    view.setFixedSize(view.size());
    game->getMap()->getPacman()->setFocus();
    return app.exec();
}