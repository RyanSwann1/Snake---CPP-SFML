#include "Window.h"



Window::Window()
{
}


Window::~Window()
{
}

void Window::setup(const std::string& windowTitle, const sf::Vector2u& windowSize)
{
	m_windowTitle = windowTitle;
	m_windowSize = windowSize;
	m_fullScreen = false;
	create();
}

void Window::draw(sf::Drawable & drawable)
{
	m_window.draw(drawable);
}

void Window::update()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed) {
			close();
		}


	}
}

bool Window::detectMouseButtonPress() const
{
	if (m_event.MouseButtonPressed)
	{
		if (m_event.mouseButton.button == sf::Mouse::Left) {
			return true;
		}
	}
	return false;
}

void Window::create()
{
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle);
	

}
