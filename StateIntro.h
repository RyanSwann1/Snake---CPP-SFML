#ifndef STATE_INTRO_H
#define STATE_INTRO_H

#include "SFML\Graphics.hpp"
#include "StateBase.h"
class StateIntro :
	public StateBase
{
public:
	StateIntro(StateManager* stateManager);
	~StateIntro() override;

	void draw() override;
	void update(const sf::Time& time) override;

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;
	
private:
	float m_elaspedTime;
	float m_timeUntilNextState;

	sf::Vector2u m_windowSize;
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Text m_introText;
	sf::Font m_introFont;
	
};
#endif // !STATE_INTRO_H

