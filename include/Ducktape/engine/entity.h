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

#ifndef DUCKTAPE_ENGINE_ENTITY_H_
#define DUCKTAPE_ENGINE_ENTITY_H_

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

    /**
     * @brief Base class for all entities.
     *
     * An entity is a game object in the game world. You may attach or remove components
     * to an entity to alter its behaviour.
     */
    class Entity
    {
    public:
        /**
         * @brief The transform component attached to this entity.
         */
        Transform *transform;

        /**
         * @brief If the entity has been destroyed or not.
         */
        bool isDestroyed = false;

        /**
         * @brief If the entity is enabled or not. You may disable an entity to stop the
         * components on it from being executed using Entity::setEnabled().
         */
        bool isEnabled = true;

        /**
         * @brief The name of the entity.
         */
        std::string name = "New Entity";

        /**
         * @brief The list of components attached to this entity.
         */
        std::vector<BehaviourScript *> components;

        /**
         * @brief The scene that this entity belongs to.
         */
        Scene *scene;

        /**
         * @brief Adds a component to the entity.
         * 
         * @tparam T The type of component to add.
         * @return T* Pointer to the component that was added.
         */
        template <typename T>
        T *AddComponent()
        {
            T *component = new T();
            component->entity = this;
            component->Constructor();
            this->components.push_back(component);
            Memory::heapMemory.push_back(component);
            return component;
        }

        /**
         * @brief Gets a component from the entity.
         * 
         * @tparam T The type of component to get.
         * @return T* Pointer to the component that was found, if component is
         * not attached to entity, nullptr is returned.
         */
        template <typename T>
        T *GetComponent()
        {
            for (auto script : this->components)
            {
                if (T *ptr = dynamic_cast<T *>(script))
                {
                    return ptr;
                }
            }
            return nullptr;
        }

        /**
         * @brief Removes a component from the entity.
         * 
         * @tparam T The type of component to remove.
         * @return If the component was successfully removed.
         */
        template <typename T>
        bool RemoveComponent()
        {
            int i = 0;
            for (auto script : this->components)
            {
                if (T *ptr = dynamic_cast<T *>(script))
                {
                    this->components.erase(this->components.begin() + i);
                    return true;
                }
                i++;
            }
            return false;
        }

        /**
         * @brief Remove a component using a pointer to the component.
         * 
         * Could be used to remove a specific component from the entity, if
         * multiple components of the same type are attached to the entity.
         */
        bool RemoveComponent(BehaviourScript *check);

        /**
         * @brief Finds an Entity in the current scene by name.
         * 
         * @param entityName 
         * @return `Entity*` Pointer to the entity that was found, nullptr if no entity was found.
         */
        static Entity *Find(std::string entityName);

        /**
         * @brief Creates a new entity in the current scene.
         * @return `Entity*` Pointer to the entity that was created.
         */
        static Entity *Instantiate();

        /**
         * @brief Creates a new entity in the current scene.
         * 
         * @param entityName The name of the entity.
         * @return `Entity*` Pointer to the entity that was created.
         */
        static Entity *Instantiate(std::string entityName);

        /**
         * @brief Creates a new entity in the current scene.
         * 
         * @param pos Position of the entity.
         * @param rot Rotation of the entity.
         * @param scl Scale of the entity.
         * @return `Entity*` Pointer to the entity that was created.
         */
        static Entity *Instantiate(Vector2 pos, float rot, Vector2 scl);

        /**
         * @brief Creates a new entity in the current scene.
         * 
         * @param entityName The name of the entity.
         * @param pos Position of the entity.
         * @param rot Rotation of the entity.
         * @param scl Scale of the entity.
         * @return `Entity*` Pointer to the entity that was created.
         */
        static Entity *Instantiate(std::string entityName, Vector2 pos, float rot, Vector2 scl);

        /**
         * @brief Destroy the entity.
         */
        void Destroy();

        /**
         * @brief Enable/Disable the entity.
         * 
         * @param isEnabled If the entity should be enabled or not.
         */
        void SetEnabled(bool isEnabled);
    };

    /**
     * @brief Destroy a component.
     */
    inline void BehaviourScript::Destroy()
    {
        this->OnDestroy();
        entity->RemoveComponent(this);
        this->isDestroyed = true;
    }
}

#endif