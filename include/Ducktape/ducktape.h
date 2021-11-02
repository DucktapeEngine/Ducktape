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
#include "include/box2d/include/box2d/box2d.h"
#include "include/json/json.hpp"
using json = nlohmann::json;

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
    
    std::vector<GameObject*> gameObjects;

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
        for(int i=0,n=gameObjects.size();i<n;i++)
        {
            if(gameObjects[i]->name == _name)
            {
                return gameObjects[i];
            }
        }
        Debug::LogError("GameObject with name \"" + _name +"\" doesn't exist!");
        return nullptr;
    }

    GameObject* GameObject::Instantiate(std::string _name)
    {
        gameObjects.push_back(new GameObject(_name));
        return gameObjects[gameObjects.size()-1];
    }

    GameObject* GameObject::Instantiate(Vector2 pos, float rot, Vector2 scl)
    {
        gameObjects.push_back(new GameObject(pos, rot, scl));
        return gameObjects[gameObjects.size()-1];
    }

    GameObject* GameObject::Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
    {
        gameObjects.push_back(new GameObject(_name, pos, rot, scl));
        return gameObjects[gameObjects.size()-1];
    }

    void Initialize(std::string _projectFilePath)
    {
        ProjectSettings::Initialize(_projectFilePath);
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

            Application::renderWindow.clear(ProjectSettings::sceneBackgroundColor.ToSFMLColor());

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
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }
    }
};


#endif
