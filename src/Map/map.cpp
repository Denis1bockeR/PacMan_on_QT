#include <fstream>
#include <string>
#include <iostream>

#include <QGraphicsProxyWidget>

#include "map.h"

Map::Map(const char* puth, ushort h, ushort w)
    : QGraphicsScene(), height(h), weight(w)
{
	ghost[0].setColor(Ghost::Red);
	ghost[1].setColor(Ghost::Orange);
	ghost[2].setColor(Ghost::Green);
	ghost[3].setColor(Ghost::Pink);
	
	readMap(puth);
}

void Map::readMap(const char* puth)
{
    std::string str;
    std::ifstream files(puth);
    int mapPosY = 0, numOtherEl = 0, numGhost = 0;
    while (getline(files, str))
    {
        int mapPosX;
        for (mapPosX = 0; mapPosX < str.length(); ++mapPosX)
        {
            int tmp_y = (mapPosY + 1) * SIZE;
            int tmp_x = (mapPosX + 1) * SIZE;

            switch (str[mapPosX])
            {
            case '1':
                otherElement.emplace_back(GameElement::tWall);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                otherElement[numOtherEl].setPixmap(QPixmap("../Texture/wall.png"));
                addWidget(&otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case 'b':
                otherElement.emplace_back(GameElement::tBall);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                otherElement[numOtherEl].setPixmap(QPixmap("../Texture/ball.png"));
                addWidget(&otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '4':
                otherElement.emplace_back(GameElement::tPowerBall);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                otherElement[numOtherEl].setPixmap(QPixmap("../Texture/powerBall.png"));
                addWidget(&otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '3':
                otherElement.emplace_back(GameElement::tBlank);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                otherElement[numOtherEl].setPixmap(QPixmap());
                addWidget(&otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '2':
                otherElement.emplace_back(GameElement::tTeleport);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                otherElement[numOtherEl].setPixmap(QPixmap("../Texture/teleport.png"));
                addWidget(&otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case 'p':
                pacman.move(tmp_x, tmp_y);
                pacman.setPos();
                addWidget(&pacman);
                break;
            case 'g':
                ghost[numGhost].move(tmp_x, tmp_y);
                ghost[numGhost].setPos();
                addWidget(&ghost[numGhost]);
                ++numGhost;
                break;
            }
        }
        ++mapPosY;
    }
}