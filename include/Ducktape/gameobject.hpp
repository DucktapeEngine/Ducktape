#pragma once
#include <string>
#include <vector>
#include "debug.hpp"
#include "scene.hpp"

class BehaviourScript;
class GameObject
{
    public:
        bool isActive = true;
        int layer = 0;
        Scene scene;
        std::string name = "New GameObject";
        std::string tag = "Default";
        // Transform transform;
        std::vector<BehaviourScript*> components;

        GameObject();

        GameObject(std::string _name);

        BehaviourScript* AddComponent(BehaviourScript* script);

        template <typename T>
        T* GetComponent() 
        {
          for(auto script:components) 
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
