#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H

#include <SFML\Graphics.hpp>
#include "StateBase.h"
class StatePause :
	public StateBase
{
public:
	StatePause(StateManager* stateManager);
	~StatePause() override;

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;

	void update(const sf::Time& timer) override;
	void draw() override; 

private:
	sf::Font m_font;
	sf::Text m_pausedText;
	float m_timeUntilResume;
	sf::Time m_timeElasped;
};
#endif // !STATE_PAUSE_H
