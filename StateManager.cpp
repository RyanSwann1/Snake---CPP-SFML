#include "StateManager.h"
#include "SharedContext.h"
#include <iostream>


StateManager::StateManager(SharedContext& sharedContext) : m_sharedContext(&sharedContext)
{
	registerState(GameState::Intro);
	registerState(GameState::MainMenu);
	registerState(GameState::Game);
	registerState(GameState::Paused);
}

StateManager::~StateManager()
{

}

void StateManager::update(sf::Time & time)
{
	//If state exists
	if (!m_states.empty())
	{
		m_states.back().second->update(time);
	}
}

void StateManager::draw()
{
	//If state exists
	if (!m_states.empty())
	{
		m_states.back().second->draw();
	}
}

void StateManager::remove(const GameState stateType)
{
	for (auto Iter = m_states.begin(); Iter != m_states.end(); Iter++)
	{
		if (stateType == Iter->first)
		{
			Iter->second->onDestroy();
			delete Iter->second;
			Iter->second = nullptr;
			m_states.erase(Iter);
			return;
		}
	}
}

void StateManager::switchToPreExistingState(const GameState gameState)
{
	//Search for pre existing state
	for (auto cIter = m_states.cbegin(); cIter != m_states.cend(); cIter++)
	{
		//If state found
		if (cIter->first == gameState)
		{
			m_states.back().second->onExit();
			StateBase* tempState = cIter->second;
			GameState tempStateType = cIter->first;
			m_states.emplace_back(tempStateType, tempState);
			m_states.back().second->onEnter();
			return;
		}
	}
}

