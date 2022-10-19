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
	enum ElementType{ tBall, tWall, tGate, tPacman, tGhost, tWeakGhost, tPowerBall };
	enum Dir { Up, Down, Right, Left, Stop };

	GameElement(ElementType type);
	~GameElement() = default;
protected:
	int x, y;
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

	void startPacman() noexcept;
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

	explicit Ghost(Color clr);
	~Ghost() = default;
private:
	Color col;
	Status status;
	QPixmap tex;
private:
	void setTexture(const char* puth) noexcept;
};

#endif // !_GAMEELEMENT_H_
