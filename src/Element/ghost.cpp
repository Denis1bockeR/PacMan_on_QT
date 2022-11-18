#include <functional>

#include "../Map/map.h"
#include "strategy.hpp"

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

void Ghost::strategySetting() noexcept
{
	if (checkDistToPacman())
	{
		switch (status)
		{
		case Ghost::Normal:
			ghostStrategy[col](this);
			break;
		case Ghost::Panic:
			break;
		}
	}
	else
	{
		switch (status)
		{
		case Ghost::Normal:
			break;
		case Ghost::Panic:
			map->setScore(Map::sGhost);
			MOVETIMER -= (MOVETIMER / (60 - Map::sGhost));
			break;
		}
	}
};
void Ghost::strategyTimeElement()
{
	strategyTimer = new QTimer();
	QObject::connect(strategyTimer, SIGNAL(timeout()), this, SLOT(strategySetting()));
	strategyTimer->start(moveSpeedFromTime());
}

void Ghost::setColor(Color clr) noexcept
{
	switch (clr)
	{
	case Ghost::Green:
		setTexture("../Texture/greenGhost.png");
		col = clr;
		break;
	case Ghost::Red:
		setTexture("../Texture/redGhost.png");
		col = clr;
		break;
	case Ghost::Yellow:
		setTexture("../Texture/yellowGhost.png");
		col = clr;
		break;
	case Ghost::Pink:
		setTexture("../Texture/pinkGhost.png");
		col = clr;
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
	return abs(x - map->getPacman()->x) > SIZE || abs(y - map->getPacman()->y) > SIZE ? true : false; 
};