#ifndef STATE_GAME_H
#define STATE_GAME_H


#include "StateBase.h"
#include "FoodSpawner.h"
#include "Snake.h"
#include "GameLogic.h"
#include <array>

enum class Difficulty { EASY, MEDIUM, HARD };
class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame() override;

	void draw() override;
	void update(const sf::Time& time) override;
	
	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;


private:
	GameLogic m_gameLogic;
	FoodSpawner m_foodSpawner;
	Snake m_snake;

	sf::Font m_font;
	std::array<sf::Text, 3> m_buttonText;
	std::array<sf::RectangleShape, 3> m_menuButtons;
	sf::Vector2f m_buttonPos;
	
	bool m_chosenDifficulty;
	float m_snakeMoveRefreshTime;

	void handleGameLogic();
	void showUI();
	void manageDifficulty(const Difficulty difficulty);
	void eventHandler();
};
#endif // !STATE_GAME_H
