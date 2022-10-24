#ifndef _GAMEELEMENT_H_
#define _GAMEELEMENT_H_

#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class GameElement : public QLabel
{
	Q_OBJECT;

public:
	enum ElementType{ tPacman, tGhost, tWeakGhost };
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
	void loadingAnim(const char* puth) noexcept;
};

class Ghost : public GameElement
{
public:
	enum Color { Red = 0, Yellow = 1, Green = 2, Pink = 3 };
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

class OtherElement : public QGraphicsPixmapItem
{
public:
	enum ElementType { tBall, tPowerBall, tWall, tBlank, tTeleport };

	OtherElement(ElementType type, QPixmap pix);
	OtherElement(const OtherElement& other);
	~OtherElement() = default;
private:
	ElementType type;
};

#endif // !_GAMEELEMENT_H_