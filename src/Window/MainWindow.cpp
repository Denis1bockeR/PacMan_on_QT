#include <fstream>
#include <string>

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include "MainWindow.h"

MainWindow::MainWindow()
	: QWidget()
{
	setFixedSize(300, 200);
	setStyleSheet("QPushButton {background-color: black; color: white; border-style: outset; border-color: blue; border-width: 2px; border-radius: 10px; fond: bold 14px;}");

    QPushButton* btnStartGame = new QPushButton("ИГРАТЬ", this);
	btnStartGame->setFixedSize(80, 30);
	btnStartGame->move(110, 40);
	QPushButton* btnRecords = new QPushButton("РЕКОРДЫ", this);
	btnRecords->setFixedSize(80, 30);
	btnRecords->move(110, 100);
	QPushButton* btnExit = new QPushButton("ВЫХОД", this);
	btnExit->setFixedSize(60, 20);
	btnExit->move(220, 160);

	QObject::connect(btnStartGame, SIGNAL(clicked()), this, SLOT(openGame()));
	QObject::connect(btnRecords, SIGNAL(clicked()), this, SLOT(openRecordWindow()));
	QObject::connect(btnExit, SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::openGame() noexcept
{
	GameWindow* game = new GameWindow("../Texture/map.txt", 20, 29);
}
void MainWindow::openRecordWindow() noexcept
{
	QWidget* recordWiget = new QWidget();
	recordWiget->setAttribute(Qt::WA_DeleteOnClose);
	recordWiget->setFixedSize(100, 100);

	QTextEdit* textRecord = new QTextEdit(recordWiget);
	textRecord->setFixedSize(recordWiget->size());
	textRecord->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	std::string s;
	std::ifstream recordFile("D:/Kursach/Pacman/records.txt");
	while (std::getline(recordFile, s))
	{
		textRecord->setPlainText(textRecord->toPlainText() +  QString::fromStdString(s) + "\n");
	}
	textRecord->setReadOnly(true);

	recordWiget->show();
}

void MainWindow::setStyleLabelSetting(QLabel& label, short y) noexcept
{
	label.setFixedSize(60, 20);
	label.move(30, y);
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("QLabel {background-color: black; color: white; fond: bold 14px;}");
}
void MainWindow::setStyleKeyLabelSetting(QLabel& label, short y) noexcept
{
	label.setFixedSize(60, 20);
	label.move(110, y);
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("QLabel {background-color: white; color: black; fond: bold 14px;}");
};