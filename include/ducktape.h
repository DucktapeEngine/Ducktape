#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std::chrono_literals;
#include "external/box2d/include/box2d/box2d.h"

namespace DT {
    #include "engine/mathf.h"
    #include "engine/vector2.h"
    #include "engine/dt_time.h"
    #include "engine/color.h"
    #include "engine/debug.h"
    #include "engine/projectsettings.h"
    #include "engine/application.h"
    class GameObject;
    #include "physics/collision.h"
    #include "engine/behaviourscript.h"
    #include "engine/componentexecutionhandler.h"
    #include "engine/transform.h"
    #include "engine/gameobject.h"
    #include "engine/input.h"
    #include "rendering/camera.h"
    #include "physics/contactlistener.h"
    #include "physics/physics.h"
    #include "rendering/renderer.h"
    #include "rendering/spriterenderer.h"
    class RevoluteJoint2D;
    class DistanceJoint2D;
    class PrismaticJoint2D;
    class WeldJoint2D;
    class PulleyJoint2D;
    class FrictionJoint2D;
    #include "physics/rigidbody.h"
    #include "physics/boxcollider.h"
    #include "physics/circlecollider.h"
    #include "physics/edgecollider.h"
    #include "physics/polygoncollider.h"
    #include "engine/scene.h"
    #include "engine/random.h"
    #include "physics/distancejoint.h"
    #include "physics/revolutejoint.h"
    #include "physics/prismaticjoint.h"
    #include "physics/weldjoint.h"
    #include "physics/pulleyjoint.h"
    #include "physics/frictionjoint.h"
    #include "audio/audiosource.h"
    
    Scene* currentScene = nullptr;

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
        while(Application::IsOpen())
        {
            ComponentExecutionHandler::FixedUpdate();
            std::this_thread::sleep_for(0.01666666666s);
        }
    }

    void Update()
    {
        ComponentExecutionHandler::Start();
        Physics::Initialize();
        Application::Initialize();

        std::thread fixedUpdateThread(FixedUpdateThread);

        // run the program as long as the window is open
        while (Application::IsOpen())
        {
            Input::Update();
            DT::Time::Update();

            Application::renderWindow.clear(ProjectSettings::sceneBackgroundColor.ToSFMLColor());

            // Start Drawing

            // for(int i=0;i<currentScene->gameObjects.size();i++)
            // {
            //     for(int j=0;j<currentScene->gameObjects[i]->components.size();j++)
            //     {
            //         if(currentScene->gameObjects[i]->components[j] != nullptr)
            //         {
            //             currentScene->gameObjects[i]->components[j]->Update();
            //         }
            //     }
            // }

            ComponentExecutionHandler::Update();
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }

        fixedUpdateThread.join();
    }
};

#endif