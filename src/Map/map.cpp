#include <fstream>
#include <string>
#include <iostream>

#include <QGraphicsProxyWidget>
#include <QTimer>

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
}
Map::~Map()
{
    for (int i = 0; i < otherElement.size(); ++i)
    {
        for (int j = 0; j < otherElement[j].size(); ++j)
        {
            delete otherElement[i][j];
        }
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
    int mapPosY = 0, numGhost = 0;
    while (getline(files, str))
    {
        otherElement.emplace_back();
        int mapPosX;
        for (mapPosX = 0; mapPosX < str.length(); ++mapPosX)
        {
            int tmp_y = 30 + mapPosY * SIZE;
            int tmp_x = mapPosX * SIZE;

            switch (str[mapPosX])
            {
            case '1':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tWall, wallPix));
                otherElement[mapPosY][mapPosX]->setPos(tmp_x, tmp_y);
                otherElement[mapPosY][mapPosX]->setZValue(-1);
                addItem(otherElement[mapPosY][mapPosX]);
                break;
            case 'b':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBall, ballPix));
                otherElement[mapPosY][mapPosX]->setPos(tmp_x, tmp_y);
                otherElement[mapPosY][mapPosX]->setZValue(-1);
                addItem(otherElement[mapPosY][mapPosX]);
                break;
            case '4':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tPowerBall, powerBallPix));
                otherElement[mapPosY][mapPosX]->setPos(tmp_x, tmp_y);
                otherElement[mapPosY][mapPosX]->setZValue(-1);
                addItem(otherElement[mapPosY][mapPosX]);
                break;
            case '3':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBlank, blankPix));
                otherElement[mapPosY][mapPosX]->setPos(tmp_x, tmp_y);
                otherElement[mapPosY][mapPosX]->setZValue(-1);
                addItem(otherElement[mapPosY][mapPosX]);
                break;
            case '2':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tTeleport, teleportPix));
                otherElement[mapPosY][mapPosX]->setPos(tmp_x, tmp_y);
                otherElement[mapPosY][mapPosX]->setZValue(-1);
                addItem(otherElement[mapPosY][mapPosX]);
                break;
            case 'p':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBlank, blankPix));

                addWidget(&pacman)->setPos(tmp_x, tmp_y);
                pacman.setPos();
                pacman.map = this;
                break;
            case 'g':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBlank, blankPix));

                addWidget(&ghost[numGhost])->setPos(tmp_x, tmp_y);
                ghost[numGhost].setPos();

                ghost[numGhost].map = this;
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
void Map::setScore(Score score) noexcept
{
    this->score += score;
    updateDispScore();

    updateMapDepenScore();
}

void Map::updateMapDepenScore()
{
    pacman.moveTimer->setInterval(pacman.moveSpeedFromTime());

    for (int i = 0; i < 4; ++i)
        ghost[i].moveTimer->setInterval(ghost[i].moveSpeedFromTime());
}
