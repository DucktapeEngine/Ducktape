/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef Entity_H
#define Entity_H

#include <string>
#include <vector>
#include <typeinfo>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/scenemanager.h>
#include <Ducktape/engine/transform.h>
#include <Ducktape/engine/memory.h>

namespace DT
{
    class Transform;

    class Entity
    {
    public:
        bool isEnabled = true;
        Transform* transform;
        bool isDestroyed = false;

        std::string name = "New Entity";
        std::vector<BehaviourScript*> components;

        Entity();

        Entity(std::string _name);

        Entity(Vector2 pos, float rot, Vector2 scl);

        Entity(std::string _name, Vector2 pos, float rot, Vector2 scl);

        template <typename T>
        T* AddComponent()
        {
            T* component = new T(this);
            this->components.push_back(component);
            Memory::heapMemory.push_back(component);
            return component;
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

        bool RemoveComponent(BehaviourScript* check);

        static Entity* Find(std::string _name);
        static Entity* Instantiate();
        static Entity* Instantiate(std::string _name);
        static Entity* Instantiate(Vector2 pos, float rot, Vector2 scl);
        static Entity* Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl);
        
        void Destroy();

        void SetEnabled(bool flag);
    };

    inline void BehaviourScript::Destroy()
    {
        this->OnDestroy();
        entity->RemoveComponent(this);
        this->isDestroyed = true;
    }
}

#endif