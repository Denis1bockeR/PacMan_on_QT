#include <functional>

#include "../Map/map.h"
#include "../gameWindow.h"
#include "strategy.hpp"

Ghost::Ghost()
	: GameElement(tGhost, 0.8f), status(Normal)
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
			ghostStrategy[4](this);
			break;
		}
	}
	else
	{
		switch (status)
		{
		case Ghost::Normal:
			map->window->writeRecords(map->getScore());
			map->endGameLose();
			break;
		case Ghost::Panic:
			map->setScore(Map::sGhost);
			MOVETIMER -= 1 + (MOVETIMER / (60 - Map::sGhost));
			if (MOVETIMER < 20)
				MOVETIMER = 20;
			respuwn();
			changeStatusNormal();
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

void Ghost::respuwn() noexcept
{
	this->QLabel::move(map->getGhastPos().first, map->getGhastPos().second + SIZE);
	setPos(pos().x(), pos().y());
}

void Ghost::changeStatusPanic() noexcept
{
	this->status = Panic;

	setPixmap(QPixmap("../Texture/weakGhost.png"));
	type = tWeakGhost;
	multiplySpeed = 0.6f;

	statusTimer->start(STATUSTIMER);
}
void Ghost::changeStatusNormal() noexcept
{
	this->status = Normal;

	setPixmap(tex);
	type = tGhost;
	multiplySpeed = 0.8f;
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