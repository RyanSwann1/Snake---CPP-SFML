#include "StateGameOver.h"
#include "StateManager.h"


StateGameOver::StateGameOver(StateManager* stateManager) : StateBase(stateManager)
{
}


StateGameOver::~StateGameOver()
{
}

void StateGameOver::onEnter()
{
}

void StateGameOver::onExit()
{
}

void StateGameOver::onCreate()
{
}

void StateGameOver::onDestroy()
{
}

void StateGameOver::update(const sf::Time & time)
{
}

void StateGameOver::draw()
{
	m_stateManager->getSharedContext()->m_window->draw(m_endingText);
}
