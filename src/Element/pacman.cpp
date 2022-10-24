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