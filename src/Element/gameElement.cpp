#include "gameElement.h"

GameElement::GameElement(ElementType type)
	: QLabel(), type(type), dir(Stop)
{
	x = pos().x();
	y = pos().y();
};
GameElement::GameElement(const GameElement& element)
{
	this->x = element.x;
	this->y = element.y;
	this->dir = element.dir;
	this->type = element.type;
}

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