#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

namespace DT
{
    int WIDTH = 600;
    int HEIGHT = 600;
    int iFrameRateLimit = 0;
    bool bVerticalSync = true;

    // including Ducktape's built-in libraries

    #include "headers/mathf.h"
    #include "headers/vector2.h"
    #include "headers/debug.h"
    #include "headers/input.h"
    #include "headers/scene.h"
    class GameObject;
    #include "headers/updateessentials.h"
    #include "headers/behaviourscript.h"
    #include "headers/gameobject.h"
    #include "headers/transform.h"
    #include "headers/camera.h"
    #include "headers/renderer.h"
    #include "headers/spriterenderer.h"

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

    std::vector<GameObject*> gameObjects;
    BehaviourScript* mainCamera;

    class TopDownController : public BehaviourScript
    {
        public:
            TopDownController()
            {
                ;
            }

            Transform* tTransform;

            void Start(UpdateEssentials* updateEssentials)
            {
                tTransform = gameObject->GetComponent<Transform>();
            }

            void Update(UpdateEssentials* updateEssentials)
            {
                tTransform->position = Camera::ScreenToWorldPos(Input::MousePosition(updateEssentials->screen), updateEssentials->screen);
            }
    };

    void ExampleScene(sf::RenderWindow& screen)
    {
        gameObjects.clear();
        int n = -1;
        gameObjects.push_back(new GameObject("Player"));
        n++;
        gameObjects[n]->AddComponent(new Transform());
        gameObjects[n]->AddComponent(new SpriteRenderer("./Assets/Characters/character_0000.png"));
        gameObjects[n]->AddComponent(new TopDownController());

        gameObjects.push_back(new GameObject("Camera"));
        n++;
        gameObjects[n]->AddComponent(new Camera());
        gameObjects[n]->AddComponent(new Transform(Vector2(0.0,0.0), 0.0, Vector2(1.0, 1.0)));
        // mainCamera = gameObjects[n]->GetComponent("Camera");
        mainCamera = gameObjects[n]->GetComponent<Camera>();
    }
};