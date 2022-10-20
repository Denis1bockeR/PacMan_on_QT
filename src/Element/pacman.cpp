#include <QTimer>

#include "gameElement.h"

Pacman::Pacman()
	: GameElement(tPacman)
{
	anim.setFileName("../Texture/startPacman.png");
	anim.start();
	setMovie(&anim);
}

void Pacman::keyPressEvent(QKeyEvent* event)
{
	switch (event->nativeVirtualKey())
	{
	case Qt::Key_D:
		dir = Right;
		loadingAnim("../Texture/rPacman.gif");

		move(++x, y);
		break;
	case Qt::Key_A:
		dir = Left;
		loadingAnim("../Texture/lPacman.gif");

		move(--x, y);
		break;
	case Qt::Key_W:
		dir = Up;
		loadingAnim("../Texture/uPacman.gif");

		move(x, --y);
		break;
	case Qt::Key_S:
		dir = Down;
		loadingAnim("../Texture/dPacman.gif");

		move(x, ++y);
		break;
	}
}
void Pacman::loadingAnim(const char* puth) noexcept
{
	anim.stop();
	anim.setFileName(puth);
	anim.start();
}