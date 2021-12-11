#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>

namespace DT
{
	struct Color 
	{
		int red = 0, blue = 0, green = 0, alpha = 255;

		Color(int _red, int _blue, int _green);

		Color(int _red, int _blue, int _green, int _alpha);

		sf::Color ToSFMLColor();
	};
}

#endif