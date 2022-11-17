#include <array>
#include <functional>

#include "../Element/gameElement.h"
#include "../Map/map.h"

std::array <std::function<void(Ghost* ghost)>, 5> ghostStrategy
{
	[](Ghost* ghost)
	{
		if (ghost->x % SIZE == 0 && (ghost->y % SIZE) - 10 == 0)
		{
			if (abs(ghost->x - ghost->getMap()->getGhastPos().first) <= 2 * SIZE && ghost->getMap()->getGhastPos().second - ghost->y <= 2 * SIZE)
			{
				if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) - 1, ghost->y / SIZE)->getType() == OtherElement::tWall)
				{
					ghost->setDir(GameElement::Right);
				}
				else
				{
					ghost->setDir(GameElement::Up);
				}
			}
			else
			{
				if (ghost->y - ghost->getMap()->getPacman()->y < 0)
				{

				}
				else if (ghost->y - ghost->getMap()->getPacman()->y > 0)
				{
					
				}
				else
				{
					if (ghost->x - ghost->getMap()->getPacman()->x < 0)
					{
						if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) - 1, ghost->y / SIZE)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Right);
						}
						else if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, (ghost->y / SIZE) + 1)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Down);
						}
					}
				}
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