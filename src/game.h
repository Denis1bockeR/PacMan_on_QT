#ifndef _GAME_H_
#define _GAME_H_

#include "Map/map.h"

class Game
{
public:
	enum Interval { GhosrNormalInterval = 10, GhostPannicInterval = 15, PacmanInterval = 10, PowerBallInterval = 10000 };

	explicit Game(const char* mapPuth, ushort h, ushort w);
	~Game();

	void moveElTimer();
	void PowerBallTimer();

	inline Map* getMap() { return map; };
private:
	Map* map;
	QTimer* timer;
private:
	void start() noexcept;
};

#endif // !_GAME_H_
