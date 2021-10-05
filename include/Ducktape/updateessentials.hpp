#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct UpdateEssentials 
{
    sf::RenderWindow* screen;
    sf::View* view;

    UpdateEssentials(sf::RenderWindow* _screen, sf::View* _view)
        : screen(_screen), view(_view)
    {
    }
};
