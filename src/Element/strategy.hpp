#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <array>
#include <functional>

#include "../Element/gameElement.h"
#include "../Map/map.h"

std::array <std::function<void(Ghost* ghost)>, 5> ghostStrategy
{
	//strategy red ghost
	[](Ghost* ghost)						
	{
		if (ghost->x % SIZE == 0 && (ghost->y % SIZE) - 10 == 0)
		{
			//gate exit
			if (abs(ghost->x - ghost->getMap()->getGhastPos().first) <= 2 * SIZE && ghost->y - ghost->getMap()->getGhastPos().second < 2 * SIZE && ghost->y - ghost->getMap()->getGhastPos().second >= 0)
			{
				if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ((ghost->y - SIZE_SCORE) / SIZE) - 1)->getType() == OtherElement::tGates)
				{
					ghost->setDir(GameElement::Up);
				}
				else if (ghost->getMap()->getGhastPos().second - ghost->y != 0)
				{
					ghost->setDir(GameElement::Right);
				}
			}
			//main alghorithm
			else
			{
				if (ghost->y - ghost->getMap()->getPacman()->y <= 0)
				{
					if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ((ghost->y - SIZE_SCORE) / SIZE) + 1)->getType() != OtherElement::tWall && ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ((ghost->y - SIZE_SCORE) / SIZE) + 1)->getType() != OtherElement::tGates)
					{
						ghost->setDir(GameElement::Down);
					}
					else if (ghost->x - ghost->getMap()->getPacman()->x >= 0)
					{
						if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) - 1, (ghost->y - SIZE_SCORE) / SIZE)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Left);
						}
						else
						{
							ghost->setDir(GameElement::Right);
						}
					}
					else if(ghost->x - ghost->getMap()->getPacman()->x < 0)
					{
						if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) + 1, (ghost->y - SIZE_SCORE) / SIZE)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Right);
						}
					}
				}
				else if (ghost->y - ghost->getMap()->getPacman()->y > 0)
				{
					if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ((ghost->y - SIZE_SCORE) / SIZE) - 1)->getType() != OtherElement::tWall)
					{
						ghost->setDir(GameElement::Up);
					}
					else if (ghost->x - ghost->getMap()->getPacman()->x >= 0)
					{
						if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) - 1, (ghost->y - SIZE_SCORE) / SIZE)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Left);
						}
						else
						{
							ghost->setDir(GameElement::Right);
						}
					}
					else
					{
						if (ghost->getMap()->getOneOtherEl((ghost->x / SIZE) + 1, (ghost->y - SIZE_SCORE) / SIZE)->getType() != OtherElement::tWall)
						{
							ghost->setDir(GameElement::Right);
						}
					}
				}
			}
		}
	},
	//strategy eyllow ghost
	[](Ghost* ghost)
	{
		if (ghost->x % SIZE == 0 && (ghost->y % SIZE) - 10 == 0 && ghost->getMap()->getOriginalNumBall() / (ghost->getMap()->getOriginalNumBall() - ghost->getMap()->getNumBall() + 1) < 3)
		{
			//gate exit, comes out where a third of the balls eaten (ghost->getMap()->getOriginalNumBall() / (ghost->getMap()->getOriginalNumBall() - ghost->getMap()->getNumBall() + 1) < 3)
			if (abs(ghost->x - ghost->getMap()->getGhastPos().first) <= 2 * SIZE && ghost->y - ghost->getMap()->getGhastPos().second < 2 * SIZE && ghost->y - ghost->getMap()->getGhastPos().second >= 0)
			{
				if (ghost->getMap()->getOneOtherEl(ghost->x / SIZE, ((ghost->y - SIZE_SCORE) / SIZE) - 1)->getType() == OtherElement::tGates)
				{
					ghost->setDir(GameElement::Up);
				}
				else if (ghost->getMap()->getGhastPos().second - ghost->y != 0)
				{
					ghost->setDir(GameElement::Left);
				}
			}
			//main alghorithm
			else
			{ 
				if (pow(ghost->x - ghost->getMap()->getPacman()->x, 2) + pow(ghost->y - ghost->getMap()->getPacman()->y, 2) > 25600)
				{
					ghostStrategy[0](ghost);
				}
				else
				{
					ghost->setDir(GameElement::Stop);
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

	}
};

#endif