#include <fstream>
#include <sstream>
#include <string>

#include <QTimer>
#include <QGraphicsView>

#include "gameWindow.h"

GameWindow::GameWindow(const char* mapPuth, ushort h, ushort w)
{
	setFocus();
	setAttribute(Qt::WA_DeleteOnClose);

	map = new Map(mapPuth, h, w);
	map->window = this;
	map->getPacman()->moveTimeElement();

	for (int i = 0; i < 4; ++i)
	{
		map->getGhost(i)->strategyTimeElement();
		map->getGhost(i)->moveTimeElement();
	}

	setScene(map);
	setBackgroundBrush(QBrush(Qt::black));
	show();
	setFixedSize(size());
	map->getPacman()->setFocus();
}
GameWindow::~GameWindow()
{
	delete map;
}

void GameWindow::openEndWindow(std::string text) noexcept
{
	QWidget* endWindow = new QWidget();
	endWindow->setAttribute(Qt::WA_DeleteOnClose);
	endWindow->setFixedSize(400, 300);

	QLabel* winText = new QLabel(endWindow);
	winText->setText(QString::fromStdString(text));
	winText->move(150, 150);

	endWindow->show();
	close();
}

void GameWindow::writeRecords(short score) noexcept
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