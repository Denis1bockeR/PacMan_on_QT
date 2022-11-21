#include <fstream>
#include <sstream>
#include <string>

#include <QTimer>
#include <QGraphicsView>
#include <QPushButton>

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
	map->getPacman()->getMoveTimer()->stop();

	for (int i = 0; i < 4; ++i)
	{
		map->getGhost(i)->getStrategyTimer()->stop();
		map->getGhost(i)->getMoveTimer()->stop();
	}

	hide();

	QWidget* endWindow = new QWidget();
	endWindow->setAttribute(Qt::WA_DeleteOnClose);
	endWindow->setFixedSize(200, 150);

	QLabel* winText = new QLabel(endWindow);
	winText->setText(QString::fromStdString(text));
	winText->setStyleSheet("QLabel {color: red; font-size: 20px;}");
	winText->move(30, 25);

	endWindow->setStyleSheet("QPushButton {background-color: black; color: white; border-style: outset; border-color: blue; border-width: 2px; border-radius: 10px; fond: bold 14px;}");

	QPushButton* restartButton = new QPushButton("Начать заново", endWindow);
	restartButton->move(55, 60);
	QPushButton* goMainMenuButton = new QPushButton("Главное меню", endWindow);
	goMainMenuButton->move(55, 100);

	QObject::connect(restartButton, &QPushButton::clicked,
		[this, endWindow]()
		{
			delete this->map;
			this->map = new Map("../Texture/map.txt", 20, 29);
			this->setScene(this->map);

			this->map->window = this;
			this->map->getPacman()->moveTimeElement();

			for (int i = 0; i < 4; ++i)
			{
				this->map->getGhost(i)->strategyTimeElement();
				this->map->getGhost(i)->moveTimeElement();
			}
			this->show();

			this->map->getPacman()->setFocus();

			endWindow->close();
		}
	);
	QObject::connect(goMainMenuButton, &QPushButton::clicked,
		[this, endWindow]()
		{
			endWindow->close();
			this->close();
		}
	);

	endWindow->show();
}

void GameWindow::writeRecords(short score) noexcept
{
	std::string s, file;
	std::fstream recordFile("D:/Kursach/Pacman/records.txt");

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