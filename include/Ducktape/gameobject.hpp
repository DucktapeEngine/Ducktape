#pragma once
#include "transform.hpp"
#include <string>
#include "debug.hpp"
#include "scene.hpp"
#include <vector>
#include "behaviourscript.hpp"

class GameObject
{
    public:
        bool isActive = true;
        int layer = 0;
        Scene scene;
        std::string name = "New GameObject";
        std::string tag = "Default";
        Transform* transform;
        std::vector<BehaviourScript*> components;

        GameObject();

        GameObject(std::string _name);

        GameObject(Vector2 pos, float rot, Vector2 scl);

        GameObject(std::string _name, Vector2 pos, float rot, Vector2 scl);

        template <typename T>
        T* AddComponent(BehaviourScript* script)
        {
            this->components.push_back(script);
            int size = this->components.size()-1;
            this->components[size]->gameObject = this;
            return (T*)this->components[size];
        }

        template <typename T>
        T* GetComponent()
        {
            for(auto script:this->components) 
            {
                if(T *ptr = dynamic_cast<T *>(script)) 
                {
                    return ptr;
                }
            }
            Debug::LogWarning(std::string("Component ") + typeid(T).name() + " not found!");
            return nullptr;
        }
};