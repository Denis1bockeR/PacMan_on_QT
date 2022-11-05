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
void GameElement::setPos(short newX, short newY)
{
	x = newX;
	y = newY;
}
void GameElement::move()
{
	short otherElX, otherElY;

	switch (dir)
	{
	case GameElement::Up:
		otherElX = (x + HALF_SIZE) / SIZE;
		otherElY = (y - SIZE_SCORE) / SIZE;

		searchTypeElement(otherElX, otherElY, x, y - 1);
		break;
	case GameElement::Down:
		otherElX = (x + HALF_SIZE) / SIZE;
		otherElY = ((y - SIZE_SCORE) / SIZE) + 1;

		searchTypeElement(otherElX, otherElY, x, y + 1);
		break;
	case GameElement::Right:
		otherElX = (x / SIZE) + 1;
		otherElY = (y - 20) / SIZE;

		searchTypeElement(otherElX, otherElY, x + 1, y);
		break;
	case GameElement::Left:
		otherElX = x / SIZE;
		otherElY = (y - 20) / SIZE;

		searchTypeElement(otherElX, otherElY, x - 1, y);
		break;
	}
}
void GameElement::moveTimeElement(ushort score)
{
	QTimer* timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
	timer->start(TIMER * cos(x / (6 * TIMER)));
}
void GameElement::searchTypeElement(short x, short y, short newX, short newY)
{
	switch (map->getOneOtherEl(x, y)->getType())
	{
	case OtherElement::tWall:
		dir = Stop;
		break;
	case OtherElement::tBall:
		map->setScore(Map::sBall);
		QLabel::move(newX, newY);
		setPos(newX, newY);
		map->getOneOtherEl(x, y)->updateType(OtherElement::tBlank);
		break;
	case OtherElement::tPowerBall:
		map->setScore(Map::sSuperBall);
		QLabel::move(newX, newY);
		setPos(newX, newY);
		map->getOneOtherEl(x, y)->updateType(OtherElement::tBlank);
		break;
	case OtherElement::tTeleport:
		break;
	case OtherElement::tBlank:
		QLabel::move(newX, newY);
		setPos(newX, newY);
		break;
	}
}

OtherElement::OtherElement(ElementType type, QPixmap pix)
	: QGraphicsPixmapItem(), type(type)
{
	setPixmap(pix);
}
OtherElement::OtherElement(const OtherElement& other)
	: type(other.type)
{}