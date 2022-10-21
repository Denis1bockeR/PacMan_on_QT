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
    QPixmap wallPix("../Texture/wall.png");
    QPixmap ballPix("../Texture/ball.png");
    QPixmap powerBallPix("../Texture/powerBall.png");
    QPixmap teleportPix("../Texture/teleport.png");
    QPixmap blankPix;

    std::string str;
    std::ifstream files(puth);
    int mapPosY = 0, numOtherEl = 0, numGhost = 0;
    while (getline(files, str))
    {
        int mapPosX;
        for (mapPosX = 0; mapPosX < str.length(); ++mapPosX)
        {
            int tmp_y = mapPosY * SIZE;
            int tmp_x = mapPosX * SIZE;

            switch (str[mapPosX])
            {
            case '1':
                otherElement.emplace_back(GameElement::tWall, wallPix);
                addWidget(&otherElement[numOtherEl]);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                ++numOtherEl;
                break;
            case 'b':
                otherElement.emplace_back(GameElement::tBall, ballPix);
                addWidget(&otherElement[numOtherEl]);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                ++numOtherEl;
                break;
            case '4':
                otherElement.emplace_back(GameElement::tPowerBall, powerBallPix);
                addWidget(&otherElement[numOtherEl]);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                ++numOtherEl;
                break;
            case '3':
                otherElement.emplace_back(GameElement::tBlank, blankPix);
                addWidget(&otherElement[numOtherEl]);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                ++numOtherEl;
                break;
            case '2':
                otherElement.emplace_back(GameElement::tTeleport, teleportPix);
                addWidget(&otherElement[numOtherEl]);
                otherElement[numOtherEl].move(tmp_x, tmp_y);
                otherElement[numOtherEl].setPos();
                ++numOtherEl;
                break;
            case 'p':
                addWidget(&pacman);
                pacman.move(tmp_x, tmp_y);
                pacman.setPos();
                break;
            case 'g':
                addWidget(&ghost[numGhost]);
                ghost[numGhost].move(tmp_x, tmp_y);
                ghost[numGhost].setPos();
                ++numGhost;
                break;
            }
        }
        ++mapPosY;
    }
}