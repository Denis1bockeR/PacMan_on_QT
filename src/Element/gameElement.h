#ifndef _GAMEELEMENT_H_
#define _GAMEELEMENT_H_

#include <functional>

#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#define TIMER 250
#define SIZE 20
#define HALF_SIZE SIZE/2

class Map;

class GameElement : public QLabel
{
	Q_OBJECT

public:
	short x, y;
public:
	enum ElementType{ tPacman, tGhost, tWeakGhost };
	enum Dir { Up, Down, Right, Left, Stop };

	GameElement(ElementType type, float multiplySpeed);
	~GameElement();

	void setPos();
	void setPos(short newX, short newY);
	void moveTimeElement(ushort score);

	inline constexpr Dir getDir() noexcept { return dir; };
public slots:
	void move();
protected:
	ElementType type;
	Dir dir;
	float multiplySpeed;

	Map* map;
	QTimer* moveTimer;

	std::function<int()> moveSpeedFromTime;
protected:
	void searchTypeElement(short x, short y, short newX, short newY);
private:
	inline bool checkDistToBall(short x, short y) noexcept { return x % 20 == 10 || (y - 30) % 20 == 10 ? true : false; };
};

class Pacman : public GameElement
{
	friend class Map;
public:
	explicit Pacman();
	~Pacman() = default;
private:
	QMovie anim;
private:
	void loadingAnim(const char* puth) noexcept;
	void keyPressEvent(QKeyEvent* event);
};

class Ghost : public GameElement
{
	friend class Map;
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

	constexpr inline ElementType getType() const noexcept { return type; };
	void updateType(ElementType type, QPixmap pix) noexcept;
private:
	ElementType type;
};

#endif // !_GAMEELEMENT_H_