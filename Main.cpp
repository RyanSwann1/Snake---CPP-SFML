#include <SFML/Graphics.hpp>
#include "Game.h"
#include <map>
#include <string>
#include <iostream>
int main()
{
	Game game;
	//Initialize Game
	if (game.init("Snake", sf::Vector2u(640, 480)))
	{
		//The game loop
		while (game.isRunning())
		{
			game.update();
			game.render();
			game.lateUpdate();
		}
	}
	//Initializatin Unsuccessful
	else
	{
		return -1;
	}
	return 0;



	char c;
	std::cin >> c;
}