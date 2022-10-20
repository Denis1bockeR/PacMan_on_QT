#include "gameElement.h"

Ghost::Ghost(Color clr)
	: GameElement(tGhost), status(Normal)
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
		setTexture("../Texture/pingGhost.png");
		break;
	}
	
	x = pos().x();
	y = pos().y();
}

constexpr void Ghost::changeStatus(Status status) noexcept
{
	this->status = status;

	if (status == Panic)
	{
		setPixmap(QPixmap("../Texture/weakGhost.png"));
		type = tWeakGhost;
	}
	else
	{
		setPixmap(tex);
		type = tGhost;
	}
}
void Ghost::setTexture(const char* puth) noexcept
{
	tex = QPixmap(puth);
	setPixmap(tex);
}