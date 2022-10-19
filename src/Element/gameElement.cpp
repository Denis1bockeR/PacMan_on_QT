#include "gameElement.h"

GameElement::GameElement(ElementType type)
	: QLabel(), type(type), dir(Stop)
{ };

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