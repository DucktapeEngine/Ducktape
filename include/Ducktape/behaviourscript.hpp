#pragma once
#include <string>

class GameObject;
class UpdateEssentials;

class BehaviourScript
{
    public:
        bool enabled = true;
        GameObject* gameObject;
        // Transform transform;
        virtual void Start(UpdateEssentials* updateEssentials);
        virtual void Update(UpdateEssentials* updateEssentials);
        virtual void FixedUpdate();
        virtual void Invoke(std::string methodName, float time);

        bool operator==(BehaviourScript script);
};