#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <array>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QString>

#include "../Element/gameElement.h"

class Map : public QGraphicsScene
{
	Q_OBJECT

public:
	enum Score { sGhost = 50, sBall = 10, sSuperBall = 30 };

	Map(const char* puth, ushort h, ushort w);
	~Map();

	inline int getSizeOtherEl() noexcept { return otherElement.size(); };
	inline OtherElement* getOneOtherEl(short x, short y) const noexcept { return otherElement[y][x]; };
	inline Pacman* getPacman() noexcept { return &pacman; };
	inline Ghost*  getGhost(Ghost::Color col)  noexcept { return &ghost[col]; };

	inline void updateDispScore() noexcept { dispScore->setPlainText("Score: " + QString::number(score)); };
	inline ushort getScore() noexcept { return score; };
private:
	ushort weight, height, score;

	QGraphicsTextItem* dispScore;
	std::vector <std::vector<OtherElement*>> otherElement;
	Pacman pacman;
	std::array<Ghost, 4> ghost;
private:
	void readMap(const char* puth);

	inline void setScore(Score score) noexcept { this->score += score; };
	void displayScore() noexcept;
};

#endif // !_MAP_H_
