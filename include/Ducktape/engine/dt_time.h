#ifndef TIME_H
#define TIME_H

#include <SFML/Window.hpp>

namespace DT
{
	namespace Time 
	{
		extern float deltaTime;
		extern sf::Clock clock;
	    extern sf::Clock deltaClock;

		void Update();
	};
}

#endif