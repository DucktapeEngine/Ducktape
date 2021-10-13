#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
<<<<<<< Updated upstream
#include <bits/stdc++.h>
=======
#include "../box2d/include/box2d/box2d.h"
#include <iostream>
#include <string>
#include <cmath>
>>>>>>> Stashed changes

namespace DT
{
    int WIDTH = 600;
    int HEIGHT = 600;
    int iFrameRateLimit = 0;
    bool bVerticalSync = true;

    // including Ducktape's built-in libraries

    #include "mathf.hpp"
    #include "vector2.hpp"
    #include "physics.hpp"
    #include "debug.hpp"
    #include "input.hpp"
    #include "scene.hpp"
    class GameObject;
    #include "updateessentials.hpp"
    #include "behaviourscript.hpp"
    #include "transform.hpp"
    #include "gameobject.hpp"
    #include "camera.hpp"
    #include "renderer.hpp"
    #include "spriterenderer.hpp"
    #include "rigidbody.hpp"

    void SplashScreen(sf::RenderWindow& screen, std::string color)
    {
        sf::Clock clock;

        while (clock.getElapsedTime().asSeconds() < 5 && screen.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (screen.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    screen.close();
            }

            screen.clear(sf::Color::White);

            if(color == "light")
            {
                sf::Texture texture;
                if (!texture.loadFromFile("./Assets/Branding/pfpFillWhite.png"))
                {
                    Debug::LogError("Error loading sprite from ./Assets/Branding/pfpFillWhite.png");
                    return;
                }

                sf::Image image;
                texture.update(image);
                texture.setSmooth(true);

                sf::Sprite sprite;
                sprite.setTexture(texture);
                sprite.setScale(0.1, 0.1);
                sprite.setOrigin(2000.0, 2000.0);
                sprite.setPosition(WIDTH/2, HEIGHT/2);

                screen.draw(sprite);
            }

            screen.display();
        }
    }

    #include "game.hpp"
};