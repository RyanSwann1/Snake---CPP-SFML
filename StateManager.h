#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "StateBase.h"
#include "StateIntro.h"
#include "StateMainMenu.h"
#include "StateGame.h"
#include "StatePause.h"

#include <vector>
#include <deque>
#include <map>
#include <SFML\System.hpp>

enum class GameState { Intro, MainMenu, Game, Paused, Credits };

struct SharedContext;
class StateManager
{
public:
	StateManager(SharedContext& sharedContext);
	~StateManager();

	void update(sf::Time& time);
	void draw();
	void remove(const GameState gameState);
	void switchToPreExistingState(const GameState gameState);
	void registerState(const GameState gameState) { m_gameStates.push_back(gameState); }
	

	template <class T>
	void switchToNewState(const GameState gameState);
	template <class T>
	void createState(const GameState gameState);

	SharedContext* getSharedContext() { return m_sharedContext; }

private:
	std::vector<GameState> m_gameStates;
	std::deque<std::pair<GameState, StateBase*>> m_states;
	//std::deque<std::pair<GameState, StateBase*>> m_moarStates;

	SharedContext* m_sharedContext;
};

template<class T>
inline void StateManager::switchToNewState(const GameState gameState)
{
	for (auto cIter = m_gameStates.cbegin(); cIter != m_gameStates.cend(); cIter++)
	{
		//If state found
		if (*cIter == gameState) 
		{
			//If already having pre existing states
			if(!m_states.empty()) {
				m_states.back().second->onExit();
			}
			//m_states.emplace(0, 
			m_states.emplace_back(gameState, new T(this));
			m_states.back().second->onCreate();
			m_states.back().second->onEnter();
		}
	}
}
template<class T>
inline void StateManager::createState(const GameState gameState)
{
	//Search fori already registered state
	for (auto &state : m_gameStates)
	{
		//If state found
		if (gameState == state)
		{
			m_states.emplace_front(gameState, new T(this));
			m_states.front().second->onCreate();
		}
	}
}
#endif // !STATE_MANAGER_H