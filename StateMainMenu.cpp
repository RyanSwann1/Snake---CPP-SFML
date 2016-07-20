#include "StateMainMenu.h"
#include "StateManager.h"
#include <iostream>


StateMainMenu::StateMainMenu(StateManager* stateManager) : StateBase(stateManager)
{
}

StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::draw()
{
	for (int i = 0; i < m_menuButton.size(); i++)
	{
		
		m_stateManager->getSharedContext()->m_window->draw(m_menuButton[i]);
		m_stateManager->getSharedContext()->m_window->draw(m_label[i]);
	}
}

void StateMainMenu::update(const sf::Time & time)
{
	onKeyDown();
}

void StateMainMenu::onCreate()
{
	m_buttonText[0].setString("1: Play");
	m_buttonText[1].setString("2: Exit");

	m_font.loadFromFile("arial.ttf");
	m_buttonSize = sf::Vector2f(300, 32);
	//Initial buttonPos
	m_buttonPos = sf::Vector2f(325, 200);

	m_menuButton[0].setSize(m_buttonSize);
	m_menuButton[0].setFillColor(sf::Color::Red);
	m_menuButton[0].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
	m_menuButton[0].setPosition(m_buttonPos);

	m_label[0].setFont(m_font);
	m_label[0].setString(m_buttonText[0].getString());
	m_label[0].setCharacterSize(16);
	sf::FloatRect labelRect = m_label[0].getLocalBounds();
	m_label[0].setOrigin(labelRect.left + (labelRect.width / 2), labelRect.top + (labelRect.height / 2));
	m_label[0].setPosition(m_menuButton[0].getPosition());


	for (int i = 1; i < m_buttonText.size(); i++)
	{
		sf::Vector2f newButtonPos = sf::Vector2f(m_menuButton[i - 1].getPosition().x, m_menuButton[i - 1].getPosition().y + 50);
		
		m_menuButton[i].setSize(m_buttonSize);
		m_menuButton[i].setFillColor(sf::Color::Red);
		m_menuButton[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_menuButton[i].setPosition(newButtonPos);

		m_label[i].setFont(m_font);
		m_label[i].setString(m_buttonText[i].getString());
		m_label[i].setCharacterSize(16);

		sf::FloatRect labelRect = m_label[i].getLocalBounds();
		m_label[i].setOrigin(labelRect.left + (labelRect.width / 2), labelRect.top + (labelRect.height / 2));
		m_label[i].setPosition(newButtonPos);
	}
	
}

void StateMainMenu::onDestroy()
{
}

void StateMainMenu::onEnter()
{
	std::cout << "You have entered the main menu state" << "\n";
}

void StateMainMenu::onExit()
{
}

void StateMainMenu::onKeyDown()
{
	//Switch to game state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		m_stateManager->switchToNewState<StateGame>(GameState::Game);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		m_stateManager->getSharedContext()->m_window->close();
	}
}
