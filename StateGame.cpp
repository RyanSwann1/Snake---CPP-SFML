#include "StateGame.h"
#include "StateManager.h"
#include "Snake.h"
#include "FoodSpawner.h"
#include <iostream>

StateGame::StateGame(StateManager* stateManger) : 
	StateBase(stateManger),
	m_snake(m_gameLogic.m_blockSize),
	m_foodSpawner(m_gameLogic.m_blockSize),
	m_chosenDifficulty(false)

{
}

StateGame::~StateGame()
{

}

void StateGame::draw()
{
	if (m_chosenDifficulty)
	{
		m_snake.render(m_stateManager->getSharedContext());
		m_foodSpawner.render(m_stateManager->getSharedContext());
	}
	else
	{
		for (int i = 0; i < m_menuButtons.size(); i++)
		{
			m_stateManager->getSharedContext()->m_window->draw(m_menuButtons[i]);
			m_stateManager->getSharedContext()->m_window->draw(m_buttonText[i]);
		}
	}
}

void StateGame::update(const sf::Time & time)
{
	eventHandler();
	if (m_chosenDifficulty)
	{
		
		m_snake.update(m_stateManager->getSharedContext(), m_foodSpawner, time);
		m_foodSpawner.update(m_stateManager->getSharedContext(), time);
	}


	//Possibly implement an event system, instead of testing this every frame
	handleGameLogic();
}

void StateGame::onCreate()
{
	std::cout << "Game State Created" << "\n";
	m_stateManager->createState<StatePause>(GameState::Paused);
}

void StateGame::onDestroy()
{
	std::cout << "Game State Destroyed" << "\n";
}

void StateGame::onEnter()
{
	//Hit up the menu for a difficulty selection screen
	std::cout << "Game State Entered" << "\n";
	showUI();
}

void StateGame::onExit()
{
	std::cout << "Game State Exited" << "\n";
}

void StateGame::handleGameLogic()
{
	if (m_snake.getScore() >= m_gameLogic.m_gameWinningScore) 
	{
		m_stateManager->switchToPreExistingState(GameState::MainMenu);
		m_stateManager->remove(GameState::Game);
	}
}


void StateGame::showUI()
{
	m_font.loadFromFile("arial.ttf");
	m_buttonText[0].setString("1: Easy");
	m_buttonText[1].setString("2: Medium");
	m_buttonText[2].setString("3: Hard");
	sf::Vector2f buttonSize(300, 32);
	m_buttonPos = sf::Vector2f(325, 200);
	float ySpaceBetweenButton = 50; // Times by 0, then 1, then 2 - thus have loop that seperates buttons easily :D
	for (int i = 0; i < m_menuButtons.size(); i++)
	{
		//Assign the position
		m_buttonPos.y += (i * ySpaceBetweenButton);

		//Set up button
		m_menuButtons[i].setFillColor(sf::Color::Red);
		m_menuButtons[i].setSize(buttonSize);
		m_menuButtons[i].setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		m_menuButtons[i].setPosition(m_buttonPos);

		//Set up button text
		m_buttonText[i].setFont(m_font);
		sf::FloatRect textRect = m_buttonText[i].getLocalBounds();
		m_buttonText[i].setCharacterSize(16);
		m_buttonText[i].setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));
		m_buttonText[i].setPosition(m_buttonPos);
		std::cout << m_buttonPos.y << "\n";
	}
}

void StateGame::manageDifficulty(const Difficulty difficulty)
{
	switch (difficulty) {
	case Difficulty::EASY:
		m_snakeMoveRefreshTime = 0.5f;
		break;

	case Difficulty::MEDIUM:
		m_snakeMoveRefreshTime = 0.25f;
		break;

	case Difficulty::HARD:
		m_snakeMoveRefreshTime = 0.1f;
		break;

	default:
		break;
	}
	m_chosenDifficulty = true;

	//When finished selecting difficulty, start game
	m_snake.init(m_snakeMoveRefreshTime);
}

void StateGame::eventHandler()
{
	if (m_chosenDifficulty)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			m_stateManager->switchToPreExistingState(GameState::Paused);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			manageDifficulty(Difficulty::EASY);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			manageDifficulty(Difficulty::MEDIUM);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
			manageDifficulty(Difficulty::HARD);
		}
	}
}
