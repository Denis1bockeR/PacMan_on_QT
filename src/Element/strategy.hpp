#include <array>
#include <functional>

#include "../Element/gameElement.h"
#include "../Map/map.h"

std::array <std::function<void(Ghost* ghost)>, 5> ghostStrategy
{
	[](Ghost* ghost)
	{
		if (abs(ghost->x - ghost->getMap()->getGhastPos().first) < SIZE + 1 && ghost->getMap()->getGhastPos().second - ghost->y < SIZE * 2 + 1)
		{
			if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ghost->y / SIZE)->getType() == OtherElement::tWall)
			{
				ghost->setDir(GameElement::Right);
			}
		}
	},
	[](Ghost* ghost)
	{

	},
	[](Ghost* ghost)
	{

	},
	[](Ghost* ghost)
	{

	},
	[](Ghost* ghost)
	{

	}
};