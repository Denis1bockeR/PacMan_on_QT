#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <array>

#include <QWidget>

#include "../game.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow();
	~MainWindow() = default;
private:
	std::array<Qt::Key, 4> controlKey;
private:
	void setStyleLabelSetting(QLabel& label, short y) noexcept;
	void setStyleKeyLabelSetting(QLabel& label, short y) noexcept;
private slots:
	void openGame() noexcept;
	void openSettingWindow() noexcept;
	void openRecordWindow() noexcept;
};

#endif