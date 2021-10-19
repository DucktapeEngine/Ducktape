#pragma once
#include <SFML/Window.hpp>

namespace Time {
	float deltaTime;
	sf::Clock clock;
    sf::Clock deltaClock;

	void Update();
};