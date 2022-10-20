#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Element/gameElement.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QGraphicsView view(new QGraphicsScene);
    Pacman* move = new Pacman();
    view.scene()->addWidget(move);
    view.show();
    move->setFocus();
    return app.exec();
}