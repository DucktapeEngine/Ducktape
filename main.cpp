#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "./ducktape.h"
#include "./game.h"
#include "bits/stdc++.h"

/*
Building with gcc for Linux:

g++ -std=c++20 main.cpp -o Ducktape -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
chown -R aryanbaburajan Ducktape
./Ducktape
*/

int main()
{
    sf::RenderWindow screen(sf::VideoMode(DT::WIDTH, DT::HEIGHT), "Ducktape", sf::Style::Default);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Renderer renderer;
    sf::Clock clock;

    // sf::RenderWindow screen(sf::VideoMode(2000, 2000), "Ducktape", sf::Style::Default, settings);
    if(iFrameRateLimit > 0 && bVerticalSync)
    {
        Debug::LogWarning("Never use both setVerticalSyncEnabled and setFramerateLimit at the same time! They would badly mix and make things worse.");
    }
    screen.setVerticalSyncEnabled(bVerticalSync);
    screen.setFramerateLimit(iFrameRateLimit);

    ExampleScene(screen);

    // run the program as long as the window is open
    while (screen.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (screen.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                screen.close();
        }

        // screen.clear(sf::Color::Black);

        // Start Draw

        for(GameObject* go:gameObjects)
        {
            for(BehaviourScript* bs:go->components)
            {
                bs->Update(screen);
            }
        }

        // Finish Draw

        screen.display();
    }

    return 0;
}