#include <QTimer>

#include "game.h"

Game::Game(const char* mapPuth, ushort h, ushort w)
{
	map = new Map(mapPuth, h, w);
	map->getPacman()->moveElement(map->getScore());
}

void Game::moveElTimer()
{
	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), map->getPacman(), SLOT(map->getPacman()->move()));
	timer->start(10);
}