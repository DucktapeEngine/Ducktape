#pragma once
#include "vector2.hpp"
#include <SFML/Graphics.hpp>

class Input
{
    public:
        inline static Vector2 MousePosition(sf::RenderWindow* screen)
        {
            sf::Vector2i vec = sf::Mouse::getPosition(*screen);
            return Vector2(vec.x, vec.y);
        }
};
