#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Application {
	// the (WIDT, HEIGHT) being 500 is temporary, the application should be running in full screen.
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, 500, 500));
	sf::RenderWindow renderWindow = sf::RenderWindow(sf::VideoMode(500, 500), "Flappy Duck", sf::Style::Default);
	void Initialize();
	bool IsOpen();
}

