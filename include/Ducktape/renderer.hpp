#pragma once
#include <SFML/Graphics.hpp>
class Vector2;
class Renderer
{
    public:
        static void DrawSprite(std::string path, Vector2 pos, sf::RenderWindow* screen);
};
