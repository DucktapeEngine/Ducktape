#include "color.h"
using namespace DT;

Color::Color(int _red, int _blue, int _green)
{
	red = _red;
	blue = _blue;
	green = _green;
	alpha = 255;
}

Color::Color(int _red, int _blue, int _green, int _alpha)
{
	red = _red;
	blue = _blue;
	green = _green;
	alpha = _alpha;
}

sf::Color Color::ToSFMLColor()
{
	return sf::Color(red, blue, green, alpha);
}