#ifndef _GAMEELEMENT_H_
#define _GAMEELEMENT_H_

#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QPixmap>
#include <QPoint>

class GameElement : public QLabel
{
	Q_OBJECT;

public:
	enum ElementType{ tBall, tWall, tTeleport, tBlank, tPacman, tGhost, tWeakGhost, tPowerBall };
	enum Dir { Up, Down, Right, Left, Stop };

	GameElement(ElementType type);
	~GameElement() = default;

	void setPos();
protected:
	short x, y;
	ElementType type;
	Dir dir;
protected slots:
	void moveElement() noexcept;
};

class Pacman : public GameElement
{
public:
	explicit Pacman();
	~Pacman() = default;
private:
	QMovie anim;
private:
	void keyPressEvent(QKeyEvent* event);
	void loadingAnim(const char* puth) noexcept;
};

class Ghost : public GameElement
{
public:
	enum Color { Red, Yellow, Pink, Green };
	enum Status { Normal, Panic };

	explicit Ghost();
	~Ghost() = default;

	void setColor(Color clr) noexcept;
	void changeStatus(Status status) noexcept;
private:
	Color col;
	Status status;
	QPixmap tex;
private:
	void setTexture(const char* puth) noexcept;
};

#endif // !_GAMEELEMENT_H_