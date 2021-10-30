#ifndef COLOR_H
#define COLOR_H

struct Color 
{
	int red = 0, blue = 0, green = 0, alpha = 255;

	Color(int _red, int _blue, int _green)
	{
		red = _red;
		blue = _blue;
		green = _green;
		alpha = 255;
	}

	Color(int _red, int _blue, int _green, int _alpha)
	{
		red = _red;
		blue = _blue;
		green = _green;
		alpha = _alpha;
	}
	
	sf::Color ToSFMLColor()
	{
		return sf::Color(red, blue, green, alpha);
	}
};

#endif