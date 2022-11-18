#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <array>

#include <QWidget>

#include "../gameWindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow();
	~MainWindow() = default;
private:
	void setStyleLabelSetting(QLabel& label, short y) noexcept;
	void setStyleKeyLabelSetting(QLabel& label, short y) noexcept;
private slots:
	void openGame() noexcept;
	void openRecordWindow() noexcept;
};

#endif