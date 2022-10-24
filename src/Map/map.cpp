#include <fstream>
#include <string>
#include <iostream>

#include <QGraphicsProxyWidget>

#include "map.h"

Map::Map(const char* puth, ushort h, ushort w)
    : QGraphicsScene(), height(h), weight(w), score(0)
{
    setMinimumRenderSize(20.0f);

	ghost[0].setColor(Ghost::Red);
	ghost[1].setColor(Ghost::Yellow);
	ghost[2].setColor(Ghost::Green);
	ghost[3].setColor(Ghost::Pink);
	
	readMap(puth);
    displayScore();
    setScore(Map::sBall);
}
Map::~Map()
{
    for (int i = 0; i < otherElement.size(); ++i)
    {
        delete otherElement[i];
        otherElement.pop_back();
    }
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
            int tmp_y = 30 + mapPosY * SIZE;
            int tmp_x = mapPosX * SIZE;

            switch (str[mapPosX])
            {
            case '1':
                otherElement.emplace_back(new OtherElement(OtherElement::tWall, wallPix));
                otherElement[numOtherEl]->setPos(tmp_x, tmp_y);
                addItem(otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case 'b':
                otherElement.emplace_back(new OtherElement(OtherElement::tBall, ballPix));
                otherElement[numOtherEl]->setPos(tmp_x, tmp_y);
                addItem(otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '4':
                otherElement.emplace_back(new OtherElement(OtherElement::tPowerBall, powerBallPix));
                otherElement[numOtherEl]->setPos(tmp_x, tmp_y);
                addItem(otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '3':
                otherElement.emplace_back(new OtherElement(OtherElement::tBlank, blankPix));
                otherElement[numOtherEl]->setPos(tmp_x, tmp_y);
                addItem(otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case '2':
                otherElement.emplace_back(new OtherElement(OtherElement::tTeleport, teleportPix));
                otherElement[numOtherEl]->setPos(tmp_x, tmp_y);
                addItem(otherElement[numOtherEl]);
                ++numOtherEl;
                break;
            case 'p':
                addWidget(&pacman)->setPos(tmp_x, tmp_y);
                pacman.setPos();
                break;
            case 'g':
                addWidget(&ghost[numGhost])->setPos(tmp_x, tmp_y);
                ghost[numGhost].setPos();
                ++numGhost;
                break;
            }
        }
        ++mapPosY;
    }
}
void Map::displayScore() noexcept
{
    dispScore = new QGraphicsTextItem("Score: " + QString::number(score));
    dispScore->setDefaultTextColor(Qt::yellow);
    dispScore->setPos(0, 0);
    addItem(dispScore);
}