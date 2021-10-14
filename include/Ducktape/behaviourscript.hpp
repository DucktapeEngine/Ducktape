#pragma once
#include <string>

class GameObject;

class BehaviourScript
{
    public:
        bool enabled = true;
        GameObject* gameObject;
        // Transform transform;
        virtual void Start();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Invoke(std::string methodName, float time);

        bool operator==(BehaviourScript script);
};
