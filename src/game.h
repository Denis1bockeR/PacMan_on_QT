#ifndef _GAME_H_
#define _GAME_H_

#include "Map/map.h"
#include <QGraphicsView>

class Game : public QGraphicsView
{
public:
	enum Interval { GhosrNormalInterval = 10, GhostPannicInterval = 15, PacmanInterval = 10, PowerBallInterval = 10000 };

	explicit Game(const char* mapPuth, ushort h, ushort w);
	~Game();

	inline Map* getMap() { return map; };
private:
	Map* map;
private:
	void start() noexcept;
	void writeRecords(short score) noexcept;
};

#endif // !_GAME_H_
