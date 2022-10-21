#ifndef _GAMEELEMENT_H_
#define _GAMEELEMENT_H_

#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QPixmap>

class GameElement : public QLabel
{
	Q_OBJECT;

public:
	enum ElementType{ tPacman, tGhost, tWeakGhost, tBall, tPowerBall, tWall, tTeleport, tBlank };
	enum Dir { Up, Down, Right, Left, Stop };

	GameElement(ElementType type);
	GameElement(const GameElement& element);
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
	enum Color { Red, Orange, Pink, Green };
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