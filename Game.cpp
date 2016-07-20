#include "Game.h"
#include "Window.h"


Game::Game() : m_stateManager(m_sharedContext)
{
	m_sharedContext.m_window = &m_window;
	m_sharedContext.m_randNumbGen = &m_randNumbGen;
}


Game::~Game()
{
}

bool Game::init(const std::string & windowTitle, const sf::Vector2u & windowSize)
{

	m_window.setup(windowTitle, windowSize);
	m_stateManager.switchToNewState<StateIntro>(GameState::Intro);
		
	//If reached, initilaizton was successful
	return true;
}

void Game::update()
{
	m_window.update();
	m_stateManager.update(m_elaspedTime);
	
}

void Game::render()
{
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate()
{
	restartClock();
}

