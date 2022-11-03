#include <QTimer>

#include "gameElement.h"

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
	switch (event->nativeVirtualKey())
	{
	case Qt::Key_D:
		dir = Right;
		loadingAnim("../Texture/rPacman.gif");

		if (checkWall((x / SIZE) + 1, (y - 20) / SIZE))
		{
			QLabel::move(x++, y);
		}
		break;
	case Qt::Key_A:
		dir = Left;
		loadingAnim("../Texture/lPacman.gif");

		if (checkWall(x / SIZE, (y - 20) / SIZE))
		{
			QLabel::move(x--, y);
		}
		break;
	case Qt::Key_W:
		dir = Up;
		loadingAnim("../Texture/uPacman.gif");

		if (checkWall((x + 10) / SIZE, (y - 30) / SIZE))
		{
			QLabel::move(x, y--);
		}
		break;
	case Qt::Key_S:
		dir = Down;
		loadingAnim("../Texture/dPacman.gif");

		if (checkWall((x + 10) / SIZE, ((y - 30) / SIZE) + 1))
		{
			QLabel::move(x, y++);
		}
		break;
	}
}