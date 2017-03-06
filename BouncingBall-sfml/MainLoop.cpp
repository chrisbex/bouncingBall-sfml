#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"
#include <vector>


int main()
{
	const int NUMBER_OF_BALLS = 10;
	const int SCREEN_WIDTH = 1440;
	const int SCREEN_HEIGHT = 900;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bouncing Ball v0.0");

	std::vector<Ball*> balls;

	for (auto i = 0; i < NUMBER_OF_BALLS; i++) 
		balls.push_back(new Ball(sf::Vector2f(i * 100 + 50, 50.0f), 30.0f, 2.0f));

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
			for (auto &it : balls) it -> update(window, sf::Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT));
		window.display();
	}

	for (auto &it : balls) delete it;
	return 0;
}