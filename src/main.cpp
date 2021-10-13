#include "../include/Ducktape/ducktape.hpp"
<<<<<<< Updated upstream
#include "bits/stdc++.h"
=======
>>>>>>> Stashed changes

using namespace DT;

/*
Building with gcc for Linux:

g++ -std=c++20 main.cpp -o Ducktape -I../include/SFML-linux-gcc/include -lsfml-graphics -lsfml-window -L../include/SFML-linux-gcc/lib -lsfml-audio -lsfml-network -lsfml-system ../include/box2d/build/bin/libbox2d.a ../include/box2d/build/bin/libglad.a ../include/box2d/build/bin/libglfw.a ../include/box2d/build/bin/libimgui.a ../include/box2d/build/bin/libsajson.a -I../
*/

int main()
{
    // world
    b2Vec2 b2Gravity(0.0, 0.0);
    b2World world(b2Gravity);
    DT::Physics physicsWorld = Physics(&world);

    // body
    // b2BodyDef bodyDef;
    // bodyDef.type = b2_dynamicBody;
    // bodyDef.position.Set(0.0f, 4.0f);
    // b2Body* body = physicsWorld.world->CreateBody(&bodyDef);

    // b2PolygonShape dynamicBox;
    // dynamicBox.SetAsBox(1.0f, 1.0f);

    // b2FixtureDef fixtureDef;
    // fixtureDef.shape = &dynamicBox;
    // fixtureDef.density = 1.0f;
    // fixtureDef.friction = 0.3f;

    // body->CreateFixture(&fixtureDef);

    float timeStep = 1.0f / 60.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // for (int32 i = 0; i < 60; ++i){
            // physicsWorld.world->Step(timeStep, velocityIterations, positionIterations);
    //     b2Vec2 position = body->GetPosition();
    //     float angle = body->GetAngle();
    //     printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    // }

    // return 0;

    {
        sf::RenderWindow screen(sf::VideoMode(DT::WIDTH, DT::HEIGHT), "Ducktape", sf::Style::Default);

        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        Renderer renderer;
        sf::Clock clock;
        sf::Clock deltaClock;

        if(iFrameRateLimit > 0 && bVerticalSync)
        {
            Debug::LogWarning("Never use both setVerticalSyncEnabled and setFramerateLimit at the same time! They would badly mix and make things worse.");
        }
        screen.setVerticalSyncEnabled(bVerticalSync);
        screen.setFramerateLimit(iFrameRateLimit);

        // DT::SplashScreen(screen, "light");

        sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
        screen.setView(view);

        ExampleScene(screen);

        // Start Loop

        UpdateEssentials updateEssentials = UpdateEssentials(&screen, &view, &physicsWorld);

        for(GameObject* go:gameObjects)
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

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->Update(&updateEssentials);
                }
            }

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->MidUpdate(&updateEssentials);
                }
            }
            
            physicsWorld.world->Step(timeStep, velocityIterations, positionIterations);

            // Late Update call

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->LateUpdate(&updateEssentials);
                }
            }

            screen.display();
        }
    }

    return 0;
}