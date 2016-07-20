#include "StatePause.h"
#include "StateManager.h"


StatePause::StatePause(StateManager* stateManager) : 
	StateBase(stateManager),
	m_timeUntilResume(1)
{
}


StatePause::~StatePause()
{
}

void StatePause::onCreate()
{
	m_font.loadFromFile("arial.ttf");
	m_pausedText.setFont(m_font);
	m_pausedText.setString("Paused");
	m_pausedText.setCharacterSize(32);
	sf::FloatRect textRect = m_pausedText.getLocalBounds();
	m_pausedText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));
	m_pausedText.setPosition(m_stateManager->getSharedContext()->m_window->getSize().x / 2.0f, m_stateManager->getSharedContext()->m_window->getSize().y / 2.0f);
}

void StatePause::onDestroy()
{
}

void StatePause::onEnter()
{
}

void StatePause::onExit()
{
}

void StatePause::update(const sf::Time & timer)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		m_stateManager->switchToPreExistingState(GameState::Game);
	}
}

void StatePause::draw()
{
	m_stateManager->getSharedContext()->m_window->draw(m_pausedText);
}
