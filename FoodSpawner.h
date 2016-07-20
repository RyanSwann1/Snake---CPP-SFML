#ifndef FOOD_SPAWNER_H
#define FOOD_SPAWNER_H

#include "SharedContext.h"
#include <SFML\Graphics.hpp>
#include <vector>
class FoodSpawner
{
public:
	FoodSpawner(float blockSize);
	~FoodSpawner();

	void update(SharedContext* sharedContext, const sf::Time& timer);
	void render(SharedContext* sharedContext);

	bool checkCollision(const sf::Vector2f& entity, const float entitySize);

private:
	std::vector<sf::Vector2i> m_apple;
	sf::Color m_appleColour;
	sf::RectangleShape m_appleShape;
	float m_timeBetweenSpawn;
	float m_nextSpawnTime;
	bool m_spawnApple;

	void spawnApple(SharedContext* sharedContext);
};
#endif // !FOOD_SPAWNER_H
