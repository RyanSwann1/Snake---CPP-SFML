#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <SFML\System\Time.hpp>
class StateManager;
class StateBase
{
	friend class StateManager;
public:
	StateBase(StateManager* stateManager) : m_stateManager(stateManager) {}
	virtual ~StateBase();

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

protected:
	StateManager* m_stateManager;
};
#endif // !STATE_BASE_H
