#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <array>
#include <QGraphicsScene>

#include "../Element/gameElement.h"

#define SIZE 20

class Map : public QGraphicsScene
{
public:
	Map(const char* puth, ushort h, ushort w);
	~Map() = default;
private:
	ushort weight, height;

	std::vector<GameElement> otherElement;
	Pacman pacman;
	std::array<Ghost, 4> ghost;
private:
	void readMap(const char* puth);
};

#endif // !_MAP_H_
