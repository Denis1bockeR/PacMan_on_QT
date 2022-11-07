#include <QTimer>

#include "game.h"

Game::Game(const char* mapPuth, ushort h, ushort w)
{
	map = new Map(mapPuth, h, w);
	map->getPacman()->moveTimeElement(map->getScore());

	for (int i = 0; i < 4; ++i)
		map->getGhost(i)->moveTimeElement(map->getScore());
}