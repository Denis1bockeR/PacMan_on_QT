#include "../Map/map.h"

Ghost::Ghost()
	: GameElement(tGhost, 0.9f), status(Normal)
{
	statusTimer = new QTimer();
	QObject::connect(statusTimer, SIGNAL(timeout()), this, SLOT(changeStatusNormal()));
}
Ghost::~Ghost()
{
	delete statusTimer;
}

void Ghost::setColor(Color clr) noexcept
{
	switch (clr)
	{
	case Ghost::Green:
		setTexture("../Texture/greenGhost.png");
		break;
	case Ghost::Red:
		setTexture("../Texture/redGhost.png");
		break;
	case Ghost::Yellow:
		setTexture("../Texture/yellowGhost.png");
		break;
	case Ghost::Pink:
		setTexture("../Texture/pinkGhost.png");
		break;
	}

}
void Ghost::changeStatusPanic() noexcept
{
	this->status = Panic;

	setPixmap(QPixmap("../Texture/weakGhost.png"));
	type = tWeakGhost;
	multiplySpeed = 0.8f;

	statusTimer->start(STATUSTIMER);
}
void Ghost::changeStatusNormal() noexcept
{
	this->status = Normal;

	setPixmap(tex);
	type = tGhost;
	multiplySpeed = 0.9f;
}

void Ghost::setTexture(const char* puth) noexcept
{
	tex = QPixmap(puth);
	setPixmap(tex);
}

bool Ghost::checkDistToPacman() noexcept
{
	return abs(x - map->getPacman()->x) < SIZE && abs(y - map->getPacman()->y) < SIZE ? true : false;
}