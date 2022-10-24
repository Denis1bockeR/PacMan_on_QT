#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <array>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QString>

#include "../Element/gameElement.h"

#define SIZE 20

class Map : public QGraphicsScene
{
public:
	enum Score { sGhost = 50, sBall = 10, sSuperBall = 30 };

	Map(const char* puth, ushort h, ushort w);
	~Map();

	inline int getSizeOtherEl() noexcept { return otherElement.size(); };
	inline std::vector<OtherElement*> getOtherEl() noexcept { return otherElement; };
	inline Pacman* getPacman() noexcept { return &pacman; };
	inline Ghost*  getGhost(Ghost::Color col)  noexcept { return &ghost[col]; };

	inline void updateDispScore() noexcept { dispScore->setPlainText("Score: " + QString::number(score)); };
private:
	ushort weight, height, score;

	QGraphicsTextItem* dispScore;
	std::vector <OtherElement*> otherElement;
	Pacman pacman;
	std::array<Ghost, 4> ghost;
private:
	void readMap(const char* puth);

	inline void setScore(Score score) noexcept { this->score += score; };
	void displayScore() noexcept;
};

//void Pacman::keyPressEvent(QKeyEvent* event)
//{
//	switch (event->nativeVirtualKey())
//	{
//	case Qt::Key_D:
//		dir = Right;
//		loadingAnim("../Texture/rPacman.gif");
//
//		move(++x, y);
//		break;
//	case Qt::Key_A:
//		dir = Left;
//		loadingAnim("../Texture/lPacman.gif");
//
//		move(--x, y);
//		break;
//	case Qt::Key_W:
//		dir = Up;
//		loadingAnim("../Texture/uPacman.gif");
//
//		move(x, --y);
//		break;
//	case Qt::Key_S:
//		dir = Down;
//		loadingAnim("../Texture/dPacman.gif");
//
//		move(x, ++y);
//		break;
//	}
//}
#endif // !_MAP_H_
