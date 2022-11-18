#include <QGraphicsWidget>

#include "../Map/map.h"
#include "../gameWindow.h"

GameElement::GameElement(ElementType type, float multiplySpeed)
	: QLabel(), type(type), dir(Stop), multiplySpeed(multiplySpeed), x(0), y(0)
{
	setFixedSize(SIZE, SIZE);

	moveSpeedFromTime = [this]() ->int { return MOVETIMER * this->multiplySpeed; };
}
GameElement::~GameElement()
{
	delete moveTimer;
}

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

//slot
void GameElement::move()
{
	if (type == tPacman)
	{
		short otherElX, otherElY;

		switch (dir)
		{
		case Up:
			otherElX = (x + HALF_SIZE) / SIZE;
			otherElY = (y - SIZE_SCORE) / SIZE;

			searchTypeElement(otherElX, otherElY, x, y - 1);
			break;
		case Down:
			otherElX = (x + HALF_SIZE) / SIZE;
			otherElY = ((y - SIZE_SCORE) / SIZE) + 1;

			searchTypeElement(otherElX, otherElY, x, y + 1);
			break;
		case Right:
			otherElX = (x / SIZE) + 1;
			otherElY = (y - SIZE) / SIZE;

			searchTypeElement(otherElX, otherElY, x + 1, y);
			break;
		case Left:
			otherElX = x / SIZE;
			otherElY = (y - SIZE) / SIZE;

			searchTypeElement(otherElX, otherElY, x - 1, y);
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case Up:
			QLabel::move(x, y--);
			break;
		case Down:
			QLabel::move(x, y++);
			break;
		case Right:
			if (map->getOneOtherEl((x / SIZE) + 1, (y - SIZE) / SIZE)->getType() == OtherElement::tTeleport)
			{
				QLabel::move(HALF_SIZE, y);
			}
			else
			{
				QLabel::move(x++, y);
			}
			break;
		case Left:
			if (map->getOneOtherEl((x / SIZE) + 1, (y - SIZE) / SIZE)->getType() == OtherElement::tTeleport)
			{
				QLabel::move(28 * SIZE - HALF_SIZE, y);
			}
			else
			{
				QLabel::move(x--, y);
			}
			break;
		}
	}
}
void GameElement::moveTimeElement()
{
	moveTimer = new QTimer();
	QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
	moveTimer->start(moveSpeedFromTime());
}
void GameElement::searchTypeElement(short x, short y, short newX, short newY)
{
	switch (map->getOneOtherEl(x, y)->getType())
	{
	case OtherElement::tWall:
		dir = Stop;
		break;
	case OtherElement::tGates:
		QLabel::move(newX, newY);
		break;
	case OtherElement::tBall:
		if (checkDistToBall(newX, newY))
		{
			map->setScore(Map::sBall);
			map->getOneOtherEl(x, y)->updateType(OtherElement::tBlank, QPixmap());
			MOVETIMER -= (MOVETIMER / (60 - Map::sBall));
			map->nBall--;
		}

		QLabel::move(newX, newY);
		setPos(newX, newY);

		break;
	case OtherElement::tPowerBall:
		if (checkDistToBall(newX, newY))
		{
			map->setScore(Map::sSuperBall);
			map->getOneOtherEl(x, y)->updateType(OtherElement::tBlank, QPixmap());
			MOVETIMER -= (MOVETIMER / (60 - Map::sSuperBall));


			for (int i = 0; i < 4; i++)
				map->getGhost(i)->changeStatusPanic();
			map->nBall--;
		}

		QLabel::move(newX, newY);
		setPos(newX, newY);

		break;
	case OtherElement::tTeleport:
		if (checkDistToBall(newX, newY))
		{
			if (dir == Right)
			{
				QLabel::move(HALF_SIZE, newY);
			}
			else
			{
				QLabel::move(28 * SIZE - HALF_SIZE, newY);
			}
		}
		else
		{
			QLabel::move(newX, newY);
		}
		setPos(pos().x(), newY);

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

void OtherElement::updateType(ElementType type, QPixmap pix)  noexcept
{
	this->type = type;
	setPixmap(pix);
}