#include "gameElement.h"

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
void GameElement::moveElement() noexcept
{
	switch (dir)
	{
	case Left:
		move(--x, y);
		break;
	case Right:
		move(++x, y);
		break;
	case Up:
		move(x, --y);
		break;
	case Down:
		move(x, ++y);
		break;
	case GameElement::Stop:
		move(x, y);
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