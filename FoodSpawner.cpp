#include "FoodSpawner.h"



FoodSpawner::FoodSpawner(float blockSize) : 
	m_appleColour(sf::Color::Red),
	m_timeBetweenSpawn(5),
	m_spawnApple(true),
	m_nextSpawnTime(0)
{
	m_appleShape.setSize(sf::Vector2f(25, 25));
	m_appleShape.setFillColor(m_appleColour);
}

FoodSpawner::~FoodSpawner()
{
}

void FoodSpawner::update(SharedContext * sharedContext, const sf::Time& timer)
{
	if (m_spawnApple) {
		spawnApple(sharedContext);
	}

}

void FoodSpawner::render(SharedContext * sharedContext)
{
	for (auto cIter = m_apple.cbegin(); cIter != m_apple.cend(); cIter++)
	{
		m_appleShape.setPosition(cIter->x, cIter->y);
		sharedContext->m_window->draw(m_appleShape);
	}
}

bool FoodSpawner::checkCollision(const sf::Vector2f & entity, const float entitySize)
{
	//Search for collision
	for (auto &apple : m_apple)
	{
		if (entity.x + entitySize > apple.x && entity.x < apple.x + m_appleShape.getSize().x &&
			entity.y + entitySize > apple.y && entity.y < apple.y + m_appleShape.getSize().y) 
		{
			m_apple.pop_back();
			m_spawnApple = true;
			return true;
		}
	}

	//No collision
	return false;
}

void FoodSpawner::spawnApple(SharedContext* sharedContext)
{
	if (m_spawnApple)
	{
		sf::Vector2i spawnPos;
		spawnPos.x = sharedContext->m_randNumbGen->getRandNumb(0, sharedContext->m_window->getSize().x - m_appleShape.getSize().x);
		spawnPos.y = sharedContext->m_randNumbGen->getRandNumb(0, sharedContext->m_window->getSize().y - m_appleShape.getSize().y);

		m_apple.push_back(spawnPos);
		m_spawnApple = false;
	}
}