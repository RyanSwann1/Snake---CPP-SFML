#include "StateIntro.h"
#include "StateManager.h"
#include "SharedContext.h"
#include <iostream>


StateIntro::StateIntro(StateManager* stateManager) : StateBase(stateManager)
{
}


StateIntro::~StateIntro()
{
}

void StateIntro::draw()
{
	m_stateManager->getSharedContext()->m_window->draw(m_introSprite);
	m_stateManager->getSharedContext()->m_window->draw(m_introText);
}

void StateIntro::update(const sf::Time & time)
{
	//std::cout << time.asSeconds() << "\n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_stateManager->switchToNewState<StateMainMenu>(GameState::MainMenu);
		m_stateManager->remove(GameState::Intro);
	}
}

void StateIntro::onCreate()
{
	std::cout << "Intro State Created." << "\n";
	m_elaspedTime = 0;
	m_windowSize = m_stateManager->getSharedContext()->m_window->getSize();

	m_introTexture.loadFromFile("Intro.png");
	m_introSprite.setTexture(m_introTexture);

	m_introSprite.setOrigin(m_introTexture.getSize().x / 2, m_introTexture.getSize().y / 2);
	m_introSprite.setPosition(m_windowSize.x / 2, 100);

	m_introFont.loadFromFile("arial.ttf");
	m_introText.setFont(m_introFont);
	m_introText.setString("Press SPACE to continue");
	m_introText.setCharacterSize(16);
	sf::FloatRect m_introTextBox = m_introText.getLocalBounds();
	m_introText.setOrigin(m_introTextBox.left + m_introTextBox.width / 2, m_introTextBox.top + m_introTextBox.height / 2);
	m_introText.setPosition(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f);
}

void StateIntro::onDestroy()
{
	std::cout << "Intro State Destroyed" << "\n";
}

void StateIntro::onEnter()
{
	std::cout << "You have entered the intro state" << "\n";
}

void StateIntro::onExit()
{
	std::cout << "Intro State Exited" << "\n";
}
