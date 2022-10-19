#include <QTimer>

#include "gameElement.h"

Pacman::Pacman()
	: GameElement(tPacman)
{
	anim.setFileName("../Texture/startPacman.png");
	anim.start();
	setMovie(&anim);

	x = pos().x();
	y = pos().y();
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

void Pacman::startPacman() noexcept
{
	QTimer* time = new QTimer();
	connect(time, SIGNAL(timeout()), this, SLOT(moveElement()));
	time->start(10);
}