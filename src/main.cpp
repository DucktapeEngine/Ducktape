#include "../include/Ducktape/ducktape.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "renderer.hpp"
#include "debug.hpp"
#include "updateessentials.hpp"
#include "gameobject.hpp"

using namespace DT;

/*
Building with gcc for Linux:

g++ -std=c++20 main.cpp -o Ducktape -I../include/SFML-linux-gcc/include -lsfml-graphics -lsfml-window -L../include/SFML-linux-gcc/lib -lsfml-audio -lsfml-network -lsfml-system
*/
constexpr static int WIDTH = 600;
constexpr static int HEIGHT = 600;

int main()
{
    sf::RenderWindow screen(sf::VideoMode(WIDTH, HEIGHT), "Ducktape", sf::Style::Default);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Renderer renderer;
    sf::Clock clock;
    sf::Clock deltaClock;

    DT::ExampleClass exampleClass;
    // sf::RenderWindow screen(sf::VideoMode(2000, 2000), "Ducktape", sf::Style::Default, settings);
    if(exampleClass.iFrameRateLimit > 0 && exampleClass.bVerticalSync)
    {
        Debug::LogWarning("Never use both setVerticalSyncEnabled and setFramerateLimit at the same time! They would badly mix and make things worse.");
    }
    screen.setVerticalSyncEnabled(exampleClass.bVerticalSync);
    screen.setFramerateLimit(exampleClass.iFrameRateLimit);

    // DT::SplashScreen(screen, "light");

    sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
    screen.setView(view);

    exampleClass.ExampleScene(screen, WIDTH, HEIGHT);

    // Start Loop

    UpdateEssentials updateEssentials = UpdateEssentials(&screen, &view);

    for(GameObject* go : exampleClass.gameObjects)
    {
        for(BehaviourScript* bs:go->components)
        {
            bs->Start(&updateEssentials);
        }
    }

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

        screen.clear(sf::Color::Black);

        // Start Draw

        for(GameObject* go: exampleClass.gameObjects)
        {
            for(BehaviourScript* bs:go->components)
            {
                bs->Update(&updateEssentials);
            }
        }

        // Finish Draw

        screen.display();
    }

    return 0;
}
