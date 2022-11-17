#include <fstream>
#include <sstream>
#include <string>

#include <QTimer>
#include <QGraphicsView>

#include "game.h"

Game::Game(const char* mapPuth, ushort h, ushort w)
{
	setFocus();
	setAttribute(Qt::WA_DeleteOnClose);

	map = new Map(mapPuth, h, w);
	map->getPacman()->moveTimeElement();

	for (int i = 0; i < 4; ++i)
	{
		map->getGhost(i)->moveTimeElement();
		map->getGhost(i)->strategyTimeElement();
	}

	setScene(map);
	setBackgroundBrush(QBrush(Qt::black));
	show();
	setFixedSize(size());
	map->getPacman()->setFocus();
}
Game::~Game()
{
	delete map;
}

void Game::writeRecords(short score) noexcept
{
	std::string s, file;
	std::fstream recordFile("D:/Kursach/Pacman/records.txt", std::ios::app);

	int i;
	for (i = 0; i < 5; i++)
	{
		if (std::getline(recordFile, s))
		{
			std::istringstream iss(s, std::istringstream::in);

			short val;
			iss >> val;
			if (score > val)
			{
				std::ostringstream ostr;
				ostr << score;
				file += ostr.str() + "\n";
				score = val;
			}
			else
			{
				file += s + "\n";
			}
		}
		else
		{
			std::ostringstream ostr;
			ostr << score;
			file += ostr.str();
			break;
		}
	}

	recordFile.close();
	recordFile.open("D:/Kursach/Pacman/records.txt", std::ios::out | std::ios::trunc);
	recordFile << file;
}