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
    #include "color.h"
    #include "renderer.h"
    #include "dt_time.h"
    #include "spriterenderer.h"
    #include "rigidbody.h"
    #include "boxcollider.h"
    #include "circlecollider.h"
    #include "edgecollider.h"
    #include "polygoncollider.h"
    
    std::vector<GameObject*> gameObjects;

    static void Instantiate(std::string _name)
    {
        gameObjects.push_back(new GameObject(_name));
    }

    static void Instantiate(Vector2 pos, float rot, Vector2 scl)
    {
       gameObjects.push_back(new GameObject(pos, rot, scl));
    }

    static void Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
    {
        gameObjects.push_back(new GameObject(_name, pos, rot, scl));
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
                if(bs != nullptr)
                {
                    bs->Start();
                }
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
                    if(bs != nullptr)
                    {
                        bs->Update();
                    }
                }
            }

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    if(bs != nullptr)
                    {
                        bs->MidUpdate();
                    }
                }
            }
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            // Late Update call

            for(GameObject* go:gameObjects)
            {
                for(BehaviourScript* bs:go->components)
                {
                    if(bs != nullptr)
                    {
                        bs->LateUpdate();
                    }
                }
            }

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }
    }
};


#endif
