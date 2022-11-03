#include <QTimer>
#include <QGraphicsWidget>

#include "../Map/map.h"

GameElement::GameElement(ElementType type)
	: QLabel(), type(type), dir(Stop)
{
	setFixedSize(20, 20);
};

void GameElement::setPos()
{
	x = pos().x();
	y = pos().y();
}
void GameElement::move()
{
	switch (dir)
	{
	case GameElement::Up:
		if (checkWall((x + 10) / SIZE, (y - 30) / SIZE))
		{
			QLabel::move(x, y--);
		}
		else
		{
			dir = Stop;
		}
		break;
	case GameElement::Down:
		if (checkWall((x + 10) / SIZE, ((y - 30) / SIZE) + 1))
		{
			QLabel::move(x, y++);
		}
		else
		{
			dir = Stop;
		}
		break;
	case GameElement::Right:
		if (checkWall((x / SIZE) + 1, (y - 20) / SIZE))
		{
			QLabel::move(x++, y);
		}
		else
		{
			dir = Stop;
		}
		break;
	case GameElement::Left:
		if (checkWall(x / SIZE, (y - 20) / SIZE))
		{
			QLabel::move(x--, y);
		}
		else
		{
			dir = Stop;
		}
		break;
	}
}
void GameElement::moveElement(ushort score)
{
	QTimer* timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(TIMER * cos(x / (6 * TIMER)));
}
bool GameElement::checkWall(short x, short y)
{
	return map->getOneOtherEl(x, y)->getType() == OtherElement::tWall ? false : true;
}

OtherElement::OtherElement(ElementType type, QPixmap pix)
	: QGraphicsPixmapItem(), type(type)
{
	setPixmap(pix);
}
OtherElement::OtherElement(const OtherElement& other)
	: type(other.type)
{}