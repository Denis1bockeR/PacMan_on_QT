#ifndef _GAME_H_
#define _GAME_H_

#include <QGraphicsView>

#include "Map/map.h"

class GameWindow : public QGraphicsView
{
public:
	enum Interval { GhosrNormalInterval = 10, GhostPannicInterval = 15, PacmanInterval = 10, PowerBallInterval = 10000 };

	explicit GameWindow(const char* mapPuth, ushort h, ushort w);
	~GameWindow();

	void openEndWindow(std::string text) noexcept;
	void writeRecords(short score) noexcept;

	inline Map* getMap() { return map; };
private:
	Map* map;
};

#endif // !_GAME_H_
