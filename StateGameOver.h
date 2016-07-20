#ifndef STATE_GAME_OVER_H
#define STATE_GAME_OVER_H

#include <SFML\Graphics.hpp>
#include "StateBase.h"
class StateGameOver :
	public StateBase
{
public:
	StateGameOver(StateManager* stateManager);
	~StateGameOver();
	
	void onEnter() override;
	void onExit() override;

	void onCreate() override;
	void onDestroy() override;

	void update(const sf::Time& time) override;
	void draw() override;

private:
	sf::Font m_textFont;
	sf::Text m_endingText;
};
#endif // !STATE_GAME_OVER_H
