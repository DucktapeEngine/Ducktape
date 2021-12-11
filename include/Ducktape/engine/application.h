#ifndef APPLICATION_H
#define APPLICATION_H

#include "vector2.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "projectsettings.h"

namespace DT
{
	namespace Application 
	{
		extern Vector2 resolution;
		extern sf::View view;
		extern sf::RenderWindow renderWindow;

		void SetResolution(Vector2 _res);

		void Initialize();

		bool IsOpen();
	}
}

#endif