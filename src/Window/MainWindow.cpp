#include <fstream>
#include <string>

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include "MainWindow.h"

MainWindow::MainWindow()
	: QWidget()
{
	setFixedSize(400, 300);
	setStyleSheet("QPushButton {background-color: black; color: white; border-style: outset; border-color: blue; border-width: 2px; border-radius: 10px; fond: bold 14px;}");

    QPushButton* btnStartGame = new QPushButton("ИГРАТЬ", this);
	btnStartGame->setFixedSize(80, 30);
	btnStartGame->move(160, 80);
	QPushButton* btnRecords = new QPushButton("РЕКОРДЫ", this);
	btnRecords->setFixedSize(80, 30);
	btnRecords->move(160, 130);
	QPushButton* btnSettings = new QPushButton("НАСТРОЙКИ", this);
	btnSettings->setFixedSize(80, 30);
	btnSettings->move(160, 180);
	QPushButton* btnExit = new QPushButton("ВЫХОД", this);
	btnExit->setFixedSize(60, 20);
	btnExit->move(320, 260);

	QObject::connect(btnStartGame, SIGNAL(clicked()), this, SLOT(openGame()));
	QObject::connect(btnSettings, SIGNAL(clicked()), this, SLOT(openSettingWindow()));
	QObject::connect(btnRecords, SIGNAL(clicked()), this, SLOT(openRecordWindow()));
	QObject::connect(btnExit, SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::openGame() noexcept
{
	Game* game = new Game("../Texture/map.txt", 20, 29);
}
void MainWindow::openSettingWindow() noexcept
{
	QWidget* settingWidget = new QWidget();
	settingWidget->setAttribute(Qt::WA_DeleteOnClose);
	settingWidget->setFixedSize(200, 190);
	settingWidget->setStyleSheet("QWidget {background-color: red;}");

	QLabel* upLabel = new QLabel("Вверх", settingWidget);
	setStyleLabelSetting(*upLabel, 20);
	QLabel* downLabel = new QLabel("Вниз", settingWidget);
	setStyleLabelSetting(*downLabel, 60);
	QLabel* leftLabel = new QLabel("Влево", settingWidget);
	setStyleLabelSetting(*leftLabel, 100);
	QLabel* rightLabel = new QLabel("Вправо", settingWidget);
	setStyleLabelSetting(*rightLabel, 140);

	QLabel* keyUpLabel = new QLabel("W", settingWidget);
	setStyleKeyLabelSetting(*keyUpLabel, 20);
	QLabel* keyDownLabel = new QLabel("S", settingWidget);
	setStyleKeyLabelSetting(*keyDownLabel, 60);
	QLabel* keyLeftLabel = new QLabel("A", settingWidget);
	setStyleKeyLabelSetting(*keyLeftLabel, 100);
	QLabel* keyRightLabel = new QLabel("D", settingWidget);
	setStyleKeyLabelSetting(*keyRightLabel, 140);

	settingWidget->show();
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