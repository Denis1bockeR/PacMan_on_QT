#include <fstream>
#include <string>
#include <iostream>

#include <QGraphicsProxyWidget>

#include "map.h"

Map::Map(const char* puth, int x, int y, ushort h, ushort w)
    : QGraphicsScene(), x(x), y(y), height(h), weight(w)
{
	ghost[0].setColor(Ghost::Red);
	ghost[1].setColor(Ghost::Yellow);
	ghost[2].setColor(Ghost::Green);
	ghost[3].setColor(Ghost::Pink);
	
	readMap(puth);

    addWidget(&pacman);
}

void Map::readMap(const char* puth)
{
    std::string str;
    std::ifstream files(puth);
    int i = 0, numGhost = 0;
    while (getline(files, str))
    {
        int j;
        for (j = 0; j < str.length(); ++j)
        {
            int tmp_x = x + (j * SIZE);
            int tmp_y = y + (i * SIZE);

            switch (str[j])
            {
            case '1':
                otherElement.push_back(GameElement::tWall);
                otherElement[i + j].move(tmp_x, tmp_y);
                otherElement[i + j].setPos();
                otherElement[i + j].setPixmap(QPixmap("../Texture/wall.png"));
                break;
            case '0':
                otherElement.push_back(GameElement::tBall);
                otherElement[i + j].move(tmp_x, tmp_y);
                otherElement[i + j].setPos();
                otherElement[i + j].setPixmap(QPixmap("../Texture/ball.png"));
                break;
            case '4':
                otherElement.push_back(GameElement::tPowerBall);
                otherElement[i + j].move(tmp_x, tmp_y);
                otherElement[i + j].setPos();
                otherElement[i + j].setPixmap(QPixmap("../Texture/powerBall.png"));
                break;
            case '3':
                otherElement.push_back(GameElement::tBlank);
                otherElement[i + j].move(tmp_x, tmp_y);
                otherElement[i + j].setPos();
                otherElement[i + j].setPixmap(QPixmap());
                break;
            case '2':
                otherElement.push_back(GameElement::tTeleport);
                otherElement[i + j].move(tmp_x, tmp_y);
                otherElement[i + j].setPos();
                otherElement[i + j].setPixmap(QPixmap("../Texture/teleport.png"));
                break;
            case 'p':
                pacman.move(tmp_x, tmp_y);
                break;
            case 'g':
                ghost[numGhost].move(tmp_x, tmp_y);
                ++numGhost;
                break;
            }

            ++i;
        }
    }
}