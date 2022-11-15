#include <fstream>
#include <string>
#include <iostream>

#include <QGraphicsProxyWidget>
#include <QTimer>

#include "map.h"

Map::Map(const char* puth, ushort h, ushort w)
    : QGraphicsScene(),  height(h), weight(w), score(0), nBall(0)
{
    setMinimumRenderSize(20.0f);

	ghost[0].setColor(Ghost::Red);
	ghost[1].setColor(Ghost::Yellow);
	ghost[2].setColor(Ghost::Green);
	ghost[3].setColor(Ghost::Pink);
	
    pacman.map = this;
    for (int i = 0; i < 4; i++)
    {
        ghost[i].map = this;
    }

	readMap(puth);

    displayScore();
}
Map::~Map()
{
    for (int i = 0; i < otherElement.size(); ++i)
    {
        for (int j = 0; j < otherElement[i].size(); ++j)
        {
            delete otherElement[i][j];
        }
    }
}

void Map::readMap(const char* puth)
{
    QPixmap wallPix("../Texture/wall.png");
    QPixmap gatesPix("../Texture/gates.png");
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
            int tmp_y = SIZE_SCORE + mapPosY * SIZE;
            int tmp_x = mapPosX * SIZE;

            switch (str[mapPosX])
            {
            case '1':
                setOtherElAttribute(OtherElement::tWall, wallPix, mapPosX, mapPosY, tmp_x, tmp_y);
                break;
            case 'h':
                setOtherElAttribute(OtherElement::tGates, gatesPix, mapPosX, mapPosY, tmp_x, tmp_y);
                X_GHAST = tmp_x;
                Y_GHAST = tmp_y;
                break;
            case 'b':
                setOtherElAttribute(OtherElement::tBall, ballPix, mapPosX, mapPosY, tmp_x, tmp_y);
                nBall++;
                break;
            case '4':
                setOtherElAttribute(OtherElement::tPowerBall, powerBallPix, mapPosX, mapPosY, tmp_x, tmp_y);
                nBall++;
                break;
            case '3':
                setOtherElAttribute(OtherElement::tBlank, blankPix, mapPosX, mapPosY, tmp_x, tmp_y);
                break;
            case '2':
                setOtherElAttribute(OtherElement::tTeleport, teleportPix, mapPosX, mapPosY, tmp_x, tmp_y);
                break;
            case 'p':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBlank, blankPix));

                addWidget(&pacman)->setPos(tmp_x, tmp_y);
                pacman.setPos();
                break;
            case 'g':
                otherElement[mapPosY].emplace_back(new OtherElement(OtherElement::tBlank, blankPix));

                addWidget(&ghost[numGhost])->setPos(tmp_x, tmp_y);
                ghost[numGhost].setPos();

                ++numGhost;
                break;
            }
        }
        ++mapPosY;
    }
}
void Map::setOtherElAttribute(OtherElement::ElementType type, QPixmap pix, short mapPosX, short mapPosY, short x, short y) noexcept
{
    otherElement[mapPosY].emplace_back(new OtherElement(type, pix));
    otherElement[mapPosY][mapPosX]->setPos(x, y);
    otherElement[mapPosY][mapPosX]->setZValue(-1);
    addItem(otherElement[mapPosY][mapPosX]);
};


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
