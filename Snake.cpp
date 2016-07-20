#include "Snake.h"
#include "FoodSpawner.h"
#include <iostream>


Snake::Snake(float blockSize) :
	m_nextMoveTime(0),
	m_bodySize(blockSize, blockSize),
	m_score(0)
{
	std::cout << "Score: " << m_score << "\n";
	m_body.setSize(sf::Vector2f(m_bodySize.x - 1, m_bodySize.y - 1));
}

Snake::~Snake()
{

}

void Snake::init(float moveRefreshRate)
{
	reset(moveRefreshRate);
}

void Snake::handleInput()
{
	if (!m_snake.empty())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_currentMoveDir != MoveDirection::LEFT) {
			m_currentMoveDir = MoveDirection::RIGHT;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_currentMoveDir != MoveDirection::RIGHT) {
			m_currentMoveDir = MoveDirection::LEFT;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_currentMoveDir != MoveDirection::DOWN) {
			m_currentMoveDir = MoveDirection::UP;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_currentMoveDir != MoveDirection::UP && m_currentMoveDir != MoveDirection::NONE) {
			m_currentMoveDir = MoveDirection::DOWN;
		}
	}
}

void Snake::update(SharedContext * sharedContext, FoodSpawner& foodSpawner, const sf::Time& elaspedTime)
{
	if (elaspedTime.asSeconds() > m_nextMoveTime)
	{
		handleInput();
		move();
		checkBounds(sharedContext);
		checkCollisions(foodSpawner);

		m_nextMoveTime = elaspedTime.asSeconds() + m_timeBetweenMove;
	}
}

void Snake::render(SharedContext* sharedContext)
{
	if (m_snake.empty()) {
		return;
	}

	//Render the head
	m_body.setFillColor(sf::Color::White);
	m_body.setPosition(m_snake.front().x, m_snake.front().y);
	sharedContext->m_window->draw(m_body);

	//Render the tail
	for (auto cIter = m_snake.cbegin() + 1; cIter != m_snake.cend(); cIter++)
	{
		m_body.setFillColor(sf::Color::Red);
		m_body.setPosition(cIter->x, cIter->y);
		sharedContext->m_window->draw(m_body);
	}

}

void Snake::move()
{
	if (m_currentMoveDir != MoveDirection::NONE)
	{
		//Move tail to previous tail element position
		for (int i = m_snake.size() - 1; i >= 1; i--)
		{
			m_snake[i] = m_snake[i - 1];
		}
	}

	//Move head
	if (m_currentMoveDir == MoveDirection::RIGHT) {
		m_snake.front().x += m_bodySize.x;
	}

	else if (m_currentMoveDir == MoveDirection::LEFT) {
		m_snake.front().x -= m_bodySize.x;
	}

	else if (m_currentMoveDir == MoveDirection::UP) {
		m_snake.front().y -= m_bodySize.y;
	}

	else if (m_currentMoveDir == MoveDirection::DOWN) {
		m_snake.front().y += m_bodySize.y;
	}
}

void Snake::extendTail()
{
	if (m_snake.size() < 2) 
	{ 
		if (m_currentMoveDir == MoveDirection::LEFT) {
			m_snake.push_back(sf::Vector2f(m_snake.front().x + m_bodySize.x, m_snake.front().y));
		}
		else if (m_currentMoveDir == MoveDirection::RIGHT) {
			m_snake.push_back(sf::Vector2f(m_snake.front().x - m_bodySize.x, m_snake.front().y));
		}
		else if (m_currentMoveDir == MoveDirection::UP) {
			m_snake.push_back(sf::Vector2f(m_snake.front().x, m_snake.front().y + m_bodySize.y));
		}
		else if (m_currentMoveDir == MoveDirection::DOWN) {
			m_snake.push_back(sf::Vector2f(m_snake.front().x, m_snake.front().y - m_bodySize.y));
		}
	}
	
	else 
	{
		//Elements in the tail
		sf::Vector2f lastElement = m_snake.back();
		sf::Vector2f secondToLastElement = m_snake.at(m_snake.size() - 2);
		if (lastElement.x == secondToLastElement.x) 
		{
			if (lastElement.y > secondToLastElement.y)
			{
				m_snake.push_back(sf::Vector2f(m_snake.back().x, m_snake.back().y + m_bodySize.y));
			}
			else
			{
				m_snake.push_back(sf::Vector2f(m_snake.back().x, m_snake.back().y - m_bodySize.y));
			}
		}
		else 
		{
			if (lastElement.x > secondToLastElement.x) {
				m_snake.push_back(sf::Vector2f(m_snake.back().x + m_bodySize.x, m_snake.back().y));
			}
			else {
				m_snake.push_back(sf::Vector2f(m_snake.back().x - m_bodySize.x, m_snake.back().y));
			}
		}
	}  
}

void Snake::checkBounds(SharedContext* sharedContext)
{
	if (m_snake.front().x < 0) {
		m_snake.front().x = sharedContext->m_window->getSize().x;
	}

	else if (m_snake.front().x > sharedContext->m_window->getSize().x) {
		m_snake.front().x = 0;
	}

	else if (m_snake.front().y < 0) {
		m_snake.front().y = sharedContext->m_window->getSize().y;
	}

	else if (m_snake.front().y > sharedContext->m_window->getSize().y) {
		m_snake.front().y = 0;
	}
}

void Snake::checkCollisions(FoodSpawner& foodSpawner)
{
	////Check collision with self
	//if(m_snake.size() > 4)
	//{ 	


	//Check collision with apple
	if (foodSpawner.checkCollision(m_snake.front(), m_bodySize.x))
	{
		extendTail();
		m_score++;
	}

}

void Snake::reset(float moveRefreshRate)
{
	m_timeBetweenMove = moveRefreshRate;
	m_currentMoveDir = MoveDirection::NONE;
	m_snake.push_back(sf::Vector2f(25, 25)); //Initial snake head position
	int initialTailSize = 3;
	//Add on the tail
	for (int i = 1; i <= initialTailSize; i++)
	{
		m_snake.push_back(sf::Vector2f(m_snake[i - 1].x, m_snake[i - 1].y += m_bodySize.y));
	}
}

void Snake::cutTail(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		m_snake.pop_back();
	}
}

