#ifndef WINDOW_H
#define WINDOW_H

#include <SFML\Graphics.hpp>
#include <string>
class Window
{
public:
	Window();
	~Window();

	void setup(const std::string& windowTitle, const sf::Vector2u& windowSize);
	void draw(sf::Drawable& drawable);
	void update();
	bool isRunning() const { return m_window.isOpen(); }

	sf::Vector2u getSize() const { return m_windowSize; }
	sf::RenderWindow& getWindow(){ return m_window; }

	void beginDraw() { m_window.clear(sf::Color::Black); }
	void endDraw() { m_window.display(); }

	bool detectMouseButtonPress() const;
	void close() { m_window.close(); }
	
private:
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	sf::Event m_event;
	bool m_fullScreen;

	void create();
	
};
#endif // !WINDOW_H
