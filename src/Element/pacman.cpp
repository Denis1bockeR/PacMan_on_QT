#include <QTimer>

#include "gameElement.h"
#include "../Map/map.h"

Pacman::Pacman()
	: GameElement(tPacman)
{
	anim.setFileName("../Texture/startPacman.png");
	anim.start();
	setMovie(&anim);
}

void Pacman::loadingAnim(const char* puth) noexcept
{
	anim.stop();
	anim.setFileName(puth);
	anim.start();
}
void Pacman::keyPressEvent(QKeyEvent* event)
{
	short otherElX, otherElY;

	switch (event->nativeVirtualKey())
	{
	case Qt::Key_D:
		dir = Right;
		loadingAnim("../Texture/rPacman.gif");

		otherElX = (x / SIZE) + 1;
		otherElY = (y - 20) / SIZE;

		searchTypeElement(otherElX, otherElY, x + 1, y);
		break;
	case Qt::Key_A:
		dir = Left;
		loadingAnim("../Texture/lPacman.gif");

		otherElX = x / SIZE;
		otherElY = (y - 20) / SIZE;

		searchTypeElement(otherElX, otherElY, x - 1, y);
		break;
	case Qt::Key_W:
		dir = Up;
		loadingAnim("../Texture/uPacman.gif");

		otherElX = (x + HALF_SIZE) / SIZE;
		otherElY = (y - SIZE_SCORE) / SIZE;

		searchTypeElement(otherElX, otherElY, x, y - 1);
		break;
	case Qt::Key_S:
		dir = Down;
		loadingAnim("../Texture/dPacman.gif");

		otherElX = (x + HALF_SIZE) / SIZE;
		otherElY = ((y - SIZE_SCORE) / SIZE) + 1;

		searchTypeElement(otherElX, otherElY, x, y + 1);
		break;
	}
}