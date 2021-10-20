#pragma once
#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "include/box2d/include/box2d/box2d.h"

namespace DT {
    #include "mathf.hpp"
    #include "vector2.hpp"
    #include "application.hpp"
    class GameObject;
    #include "debug.hpp"
    #include "behaviourscript.hpp"
    #include "transform.hpp"
    #include "gameobject.hpp"
    #include "input.hpp"
    #include "camera.hpp"
    #include "physics.hpp"
    #include "renderer.hpp"
    #include "time.hpp"
    #include "spriterenderer.hpp"
    #include "rigidbody.hpp"
    
    std::vector<GameObject*> gameObjects;

    void Initialize()
    {
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