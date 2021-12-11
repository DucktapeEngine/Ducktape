#ifndef Entity_H
#define Entity_H

#include <string>
#include <vector>
#include "behaviourscript.h"
#include "scenemanager.h"
#include "transform.h"

namespace DT
{
    class Transform;

    class Entity
    {
    public:
        bool isActive = true;
        int layer = 0;
        Transform* transform;
        std::string name = "New Entity";
        std::string tag = "Default";
        std::vector<BehaviourScript*> components;

        Entity();

        Entity(std::string _name);

        Entity(Vector2 pos, float rot, Vector2 scl);

        Entity(std::string _name, Vector2 pos, float rot, Vector2 scl);

        template <typename T>
        T* AddComponent()
        {
            this->components.push_back(new T());
            int size = this->components.size()-1;
            this->components[size]->entity = this;
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

        static Entity* Find(std::string _name);
        static Entity* Instantiate();
        static Entity* Instantiate(std::string _name);
        static Entity* Instantiate(Vector2 pos, float rot, Vector2 scl);
        static Entity* Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl);
    };
}

#endif