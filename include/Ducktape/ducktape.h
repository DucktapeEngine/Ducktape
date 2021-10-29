#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
#include "include/box2d/include/box2d/box2d.h"


namespace DT {
    #include "mathf.h"
    #include "vector2.h"
    #include "application.h"
    class GameObject;
    #include "debug.h"
    #include "behaviourscript.h"
    #include "transform.h"
    #include "gameobject.h"
    #include "input.h"
    #include "camera.h"
    #include "physics.h"
    #include "renderer.h"
    #include "time.h"
    #include "spriterenderer.h"
    #include "rigidbody.h"
    
    std::vector<GameObject*> gameObjects;


    static bool Instantiate(std::string _name)
    {
        GameObject gameObj(_name);
        gameObjects.push_back(gameObj);
    }

    static bool Instantiate(Vector2 pos, float rot, Vector2 scl)
    {
        GameObject gameObj(pos, rot, scl);
        gameObjects.push_back(gameObj);
    }

    static bool Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
    {
        GameObject gameObj(_name, pos, rot, scl);
        gameObjects.push_back(gameObj);
    }

    void Initialize()
    {
        // Vector2::*Down = Vector2(0.0f, -1.0f);
        Physics::Initialize();
        Application::Initialize();
    }

    void Update()
    {
        for(GameObject* go:gameObjects)
        {
            for(BehaviourScript* bs:go->components)
            {
                bs->Start();
            }
        }

        // run the program as long as the window is open
        while (Application::IsOpen())
        {
            Input::Update();
            DT::Time::Update();

            Application::renderWindow.clear(sf::Color::Black);

            // Start Draw

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->Update();
                }
            }

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->MidUpdate();
                }
            }
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            // Late Update call

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    bs->LateUpdate();
                }
            }

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }
    }
};


#endif
