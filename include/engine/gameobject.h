#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "behaviourscript.h"
#include "scenemanager.h"
#include "transform.h"

namespace DT
{
    class Transform;

    class GameObject
    {
    public:
        bool isActive = true;
        int layer = 0;
        Transform* transform;
        std::string name = "New GameObject";
        std::string tag = "Default";
        std::vector<BehaviourScript*> components;

        GameObject();

        GameObject(std::string _name);

        GameObject(Vector2 pos, float rot, Vector2 scl);

        GameObject(std::string _name, Vector2 pos, float rot, Vector2 scl);

        template <typename T>
        T* AddComponent()
        {
            this->components.push_back(new T());
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

        template <typename T>
        bool RemoveComponent()
        {
            int i=0;
            for(auto script:this->components)
            {
                if(T *ptr = dynamic_cast<T *>(script))
                {
                    this->components.erase(this->components.begin()+i);
                    return true;
                }
                i++;
            }
            return false;
        }

        static GameObject* Find(std::string _name);
        static GameObject* Instantiate();
        static GameObject* Instantiate(std::string _name);
        static GameObject* Instantiate(Vector2 pos, float rot, Vector2 scl);
        static GameObject* Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl);
    };
}

#endif