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

void Ghost::setTexture(const char* puth) noexcept
{
	tex = QPixmap(puth);
	setPixmap(tex);
	setFixedSize(20, 20);
}