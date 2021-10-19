#pragma once
#include "gameobject.hpp"
#include "scene.hpp"
#include "component.hpp"

class BehaviourScript;

class BehaviourScript: public Component
{
    public:
        bool enabled = true;
        virtual void Start();
        virtual void Update();
        virtual void MidUpdate();
        virtual void LateUpdate();
        void Invoke(std::string methodName, float time);

        bool operator==(BehaviourScript script);
};