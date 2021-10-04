#pragma once

struct UpdateEssentials 
{
    sf::RenderWindow* screen;
    sf::View* view;
    DT::Physics* physicsWorld;

    UpdateEssentials(sf::RenderWindow* _screen, sf::View* _view, DT::Physics* _physicsWorld)
    {
        screen = _screen;
        view = _view;
        physicsWorld = _physicsWorld;
    }
};