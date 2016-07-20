#ifndef SNAKE_H
#define SNAKE_H

#include "SharedContext.h"
#include <SFML\Graphics.hpp>
#include <deque>

enum class MoveDirection { LEFT, RIGHT, UP, DOWN, NONE };
struct SnakeContainer
{
	SnakeContainer(float x, float y) : m_position(x, y) {}
	sf::Vector2f m_position;
};

class FoodSpawner;
class Snake
{
public:
	Snake(float blockSize);
	~Snake();

	void init(float m_moveRefreshRate);
	void handleInput();
	void update(SharedContext* sharedContext, FoodSpawner& foodSpawner, const sf::Time& elapsedTime);
	void render(SharedContext* sharedContext);

	int getScore() const { return m_score; }

private:
	sf::Vector2f m_bodySize;
	std::deque<sf::Vector2f> m_snake;
	MoveDirection m_currentMoveDir;
	sf::RectangleShape m_body;

	float m_timeBetweenMove;
	float m_nextMoveTime;
	int m_score;
	
	void move();
	void extendTail();
	void checkBounds(SharedContext* sharedContext);
	void checkCollisions(FoodSpawner& foodSpawner);
	void reset(float moveRefreshRate);
	void cutTail(int amount);
};

#endif // !SNAKE_H