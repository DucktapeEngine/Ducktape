#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;
#include "include/box2d/include/box2d/box2d.h"

namespace DT {
    #include "mathf.h"
    #include "vector2.h"
    #include "dt_time.h"
    #include "color.h"
    #include "debug.h"
    #include "projectsettings.h"
    #include "application.h"
    class GameObject;
    #include "collision.h"
    #include "behaviourscript.h"
    #include "transform.h"
    #include "gameobject.h"
    #include "input.h"
    #include "camera.h"
    #include "contactlistener.h"
    #include "physics.h"
    #include "renderer.h"
    #include "spriterenderer.h"
    #include "rigidbody.h"
    #include "boxcollider.h"
    #include "circlecollider.h"
    #include "edgecollider.h"
    #include "polygoncollider.h"
    #include "scene.h"
    #include "random.h"
    
    Scene* currentScene = nullptr;
    bool isRunning = false;

    Vector2 Transform::SetPosition(Vector2 _pos)
    {
        position = _pos;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateLocalValues();
        return _pos;
    }

    float Transform::SetRotation(float _rot)
    {
        rotation = _rot;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateLocalValues();
        return _rot;
    }

    Vector2 Transform::SetScale(Vector2 _scl)
    {
        scale = _scl;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateLocalValues();
        return _scl;
    }

    Vector2 Transform::SetLocalPosition(Vector2 _pos)
    {
        position = _pos;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateWorldValues();
        return _pos;
    }

    float Transform::SetLocalRotation(float _rot)
    {
        rotation = _rot;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateWorldValues();
        return _rot;
    }

    Vector2 Transform::SetLocalScale(Vector2 _scl)
    {
        scale = _scl;
        for(BehaviourScript* bs:gameObject->components)
        {
            if(bs != nullptr)
            {
                bs->OnTransformChange();
            }
        }
        RecalculateWorldValues();
        return _scl;
    }

    GameObject* GameObject::Find(std::string _name)
    {
        for(int i=0,n=currentScene->gameObjects.size();i<n;i++)
        {
            if(currentScene->gameObjects[i]->name == _name)
            {
                return currentScene->gameObjects[i];
            }
        }
        Debug::LogError("GameObject with name \"" + _name +"\" doesn't exist!");
        return nullptr;
    }

    GameObject* GameObject::Instantiate(std::string _name)
    {
        currentScene->gameObjects.push_back(new GameObject(_name));
        return currentScene->gameObjects[currentScene->gameObjects.size()-1];
    }

    GameObject* GameObject::Instantiate(Vector2 pos, float rot, Vector2 scl)
    {
        currentScene->gameObjects.push_back(new GameObject(pos, rot, scl));
        return currentScene->gameObjects[currentScene->gameObjects.size()-1];
    }

    GameObject* GameObject::Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
    {
        currentScene->gameObjects.push_back(new GameObject(_name, pos, rot, scl));
        return currentScene->gameObjects[currentScene->gameObjects.size()-1];
    }

    void Scene::LoadScene(Scene* _scene)
    {
        if(currentScene != nullptr)
        {
            currentScene->Destroy();
        }
        currentScene = _scene;
        currentScene->Initialize();
    }

    void FixedUpdateThread()
    {
        while(Application::isRunning)
        {
            for(int i=0;i<currentScene->gameObjects.size();i++)
            {
                for(int j=0;j<currentScene->gameObjects[i]->components.size();j++)
                {
                    if(currentScene->gameObjects[i]->components[j] != nullptr)
                    {
                        currentScene->gameObjects[i]->components[j]->FixedUpdate();
                    }
                }
            }
            std::this_thread::sleep_for(0.01666666666s);
        }
    }

    void Update()
    {
        for(int i=0;i<currentScene->gameObjects.size();i++)
        {
            for(int j=0;j<currentScene->gameObjects[i]->components.size();j++)
            {
                if(currentScene->gameObjects[i]->components[j] != nullptr)
                {
                    currentScene->gameObjects[i]->components[j]->Start();
                    currentScene->gameObjects[i]->components[j]->started = true;
                }
            }
        }

        Physics::Initialize();
        Application::Initialize();

        Application::isRunning = true;

        std::thread fixedUpdateThread(FixedUpdateThread);

        // run the program as long as the window is open
        while (Application::IsOpen())
        {
            Input::Update();
            DT::Time::Update();

            Application::renderWindow.clear(ProjectSettings::sceneBackgroundColor.ToSFMLColor());

            // Start Drawing

            for(int i=0;i<currentScene->gameObjects.size();i++)
            {
                for(int j=0;j<currentScene->gameObjects[i]->components.size();j++)
                {
                    if(currentScene->gameObjects[i]->components[j] != nullptr)
                    {
                        currentScene->gameObjects[i]->components[j]->Update();
                    }
                }
            }
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }

        Application::isRunning = false;

        fixedUpdateThread.join();
    }
};


#endif