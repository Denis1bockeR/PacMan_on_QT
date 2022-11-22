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

	QPushButton* btnHelp = new QPushButton("СПРАВКА", this);

    QPushButton* btnStartGame = new QPushButton("ИГРАТЬ", this);
	btnStartGame->setFixedSize(80, 30);
	btnStartGame->move(110, 40);
	QPushButton* btnRecords = new QPushButton("РЕКОРДЫ", this);
	btnRecords->setFixedSize(80, 30);
	btnRecords->move(110, 100);
	QPushButton* btnExit = new QPushButton("ВЫХОД", this);
	btnExit->setFixedSize(60, 20);
	btnExit->move(220, 160);

	QObject::connect(btnHelp, SIGNAL(clicked()), this, SLOT(openHelpWindow()));
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
	std::ifstream recordFile("../records.txt");
	while (std::getline(recordFile, s))
	{
		textRecord->setPlainText(textRecord->toPlainText() +  QString::fromStdString(s) + "\n");
	}
	textRecord->setReadOnly(true);

	recordWiget->show();
}
void MainWindow::openHelpWindow() noexcept
{
	QWidget* helpWindow = new QWidget();
	helpWindow->setAttribute(Qt::WA_DeleteOnClose);
	helpWindow->setFixedSize(100, 100);
	helpWindow->setStyleSheet("QPushButton {background-color: black; color: white;}");

	QPushButton* helpAuthorWindow = new QPushButton("Об авторе", helpWindow);
	helpAuthorWindow->move(20, 20);
	helpAuthorWindow->setFixedSize(60, 20);
	QPushButton* helpProgramWindow = new QPushButton("О программе", helpWindow);
	helpProgramWindow->move(10, 60);
	helpProgramWindow->setFixedSize(80, 20);

	QObject::connect(helpAuthorWindow, &QPushButton::clicked,
		[]()
		{
			QWidget* authorHelpWindow = new QWidget();
			authorHelpWindow->setAttribute(Qt::WA_DeleteOnClose);

			QLabel* authorTextHelp = new QLabel(authorHelpWindow);
			authorTextHelp->setText("Разработчик: Трофимов Денис Александрович, 2003 года рождения\nУчащийся ИПФ БНТУ группа 10903520");
			authorTextHelp->setAlignment(Qt::AlignCenter);

			authorHelpWindow->setFixedSize(380, 40);

			authorHelpWindow->show();
		}
	);
	QObject::connect(helpProgramWindow, &QPushButton::clicked,
		[]()
		{
			QWidget* programHelpWindow = new QWidget();
			programHelpWindow->setAttribute(Qt::WA_DeleteOnClose);

			QLabel* programTextHelp = new QLabel(programHelpWindow);
			programTextHelp->setText("PacMan представляет собой аркадную игру, где игрок управляя PacMan-ом с помощью клавиш WASD, должен собрать все шарики\nЕсли PacMan столкнется с призраком он проиграет.\nПри этом если съесть большой шарик, то будет 10 секунд на то, чтобы съесть призрака");
			programTextHelp->setAlignment(Qt::AlignCenter);

			programHelpWindow->setFixedSize(735, 60);

			programHelpWindow->show();
		}
	);

	helpWindow->show();
}

void MainWindow::setStyleLabelSetting(QLabel& label, short y) noexcept
{
	label.setFixedSize(60, 20);
	label.move(30, y);
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("QLabel {background-color: black; color: white; fond: bold 14px;}");
}
void MainWindow::keyPressEvent(QKeyEvent * event)
{
	switch (event->nativeVirtualKey())
	{
	case Qt::Key_F1:
		openHelpWindow();
		break;
	}
};