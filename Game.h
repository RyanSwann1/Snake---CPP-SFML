#ifndef GAME_H
#define GAME_H

#include <string>
#include <SFML\Graphics.hpp>
#include "RandNumberGenerator.h"
#include "SharedContext.h"
#include "StateManager.h"
class Window;
class Game
{
public:
	Game();
	~Game();

	bool init(const std::string& windowTitle, const sf::Vector2u& windowSize);

	void update();
	void render();
	void lateUpdate();

	bool isRunning() const { return m_window.isRunning(); }


private:

	sf::Clock m_clock;
	sf::Time m_elaspedTime;
	Window m_window;	
	SharedContext m_sharedContext; 
	StateManager m_stateManager;
	RandNumberGenerator m_randNumbGen;
	void restartClock() { m_elaspedTime += m_clock.restart(); }
	
};
#endif // !GAME_H
