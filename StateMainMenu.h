#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H


#include <map>
#include <string>
#include <array>
#include "StateBase.h"
#include <SFML\Graphics.hpp>
class StateMainMenu :
	public StateBase
{
public:
	StateMainMenu(StateManager* stateManager);
	~StateMainMenu() override;

	void draw() override;
	void update(const sf::Time& time) override;

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;

private:
	std::array<sf::Text, 2> m_buttonText;
	std::array<sf::Text, 2> m_label;
	std::array<sf::RectangleShape, 2> m_menuButton;
	sf::Font m_font;
	sf::Vector2f m_buttonPos;
	sf::Vector2f m_buttonSize;

	void onKeyDown();
};
#endif // !STATE_MAIN_MENU_H