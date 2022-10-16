/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <string>
#include <iostream>
#include <array>

#include <entt/entt.hpp>
#include <Renderer/ImGui.h>

#include <Core/Platform.h>
#include <Scene/System.h>
#include <Scene/Entity.h>
#include <Core/Macro.h>

namespace DT
{
    class Scene;
    class Engine;
    class Camera;

    enum RegisterAction
    {
        AddSystem,
        Assign,
        Remove
    };

    typedef void (*RegisterRuntimeFunc)(Scene &);
    typedef void (*RegisterFunc)(Entity, Scene &, RegisterAction);

    class Scene
    {
    protected:
        class SystemPool
        {
        public:
            char* pData {nullptr};
            unsigned int noAllocatedSystems = 0;

            SystemPool()
            {
                pData = new char[sizeof(System) * MAX_SYSTEMS];
            }

            ~SystemPool()
            {
                delete[] pData;
            }

            inline void* Get(size_t index)
            {
                return pData + index * sizeof(System);
            }

            class Iterator
            {
            public:
                unsigned int idx;
                SystemPool *systemPool;

                Iterator(SystemPool *pool, unsigned int index) : systemPool(pool), idx(index) {}

                System *operator*() const
                {
                    return (System *)systemPool->Get(idx);
                }

                bool operator==(const Iterator& other) const
                {
                    return idx == other.idx;
                }

                bool operator!=(const Iterator& other) const
                {
                    return idx != other.idx;
                }

                Iterator& operator++()
                {
                    idx++;
                    return *this;
                }
            };

            const Iterator begin()
            {
                return Iterator(this, 0);
            }

            const Iterator end()
            {
                return Iterator(this, noAllocatedSystems - 1);
            }
        };

        SystemPool systems;
    public:
        entt::registry sceneRegistry;           ///< @brief Registry of all the components and entities in the scene
        Engine *engine;                         ///< @brief Pointer to the engine instance
        Camera *activeCamera;                   ///< @brief Active camera of the scene
        bool initialized = false;               ///< @brief Component initialization state
        Module gameModule;                      ///< @breif Dll containing the game
        Entity selectedEntity;

        Scene(Engine *holderEngine);
        ~Scene();

        template <typename T, typename... Args>
        T *Register(Args &&...args)
        {
            T *system = new (systems.Get(systems.noAllocatedSystems)) T(std::forward<Args>(args)...);
            systems.noAllocatedSystems++;
            return system;
        }

        template <typename T>
        bool Has(Entity entity)
        {
            return sceneRegistry.any_of<T>(entity);
        }

        template <typename T>
        T &Assign(Entity entity)
        {
            DT_ASSERT(!Has<T>(entity), "Entity already has component.");

            T &component = sceneRegistry.emplace<T>(entity);
            
            return component;
        }

        template <typename T>
        T &Require(Entity entity)
        {
            if (Has<T>(entity))
                return Get<T>(entity);

            return Assign<T>(entity);
        }

        template <typename T>
        T &Get(Entity entity)
        {
            DT_ASSERT(Has<T>(entity), "Entity does not have component.");

            return sceneRegistry.get<T>(entity);
        }

        template <typename T>
        void Remove(Entity entity)
        {
            DT_ASSERT(Has<T>(entity), "Entity does not have component.");

            // sceneRegistry.get<T>(entity).Destroy(); //TOFIX: Destroy currently not called
            sceneRegistry.remove<T>(entity);
        }

        template <typename... Components>
        auto View()
        {
            return sceneRegistry.view<Components...>();
        }

        template <typename T>
        static Entity From(T &component, Scene &scene)
        {
            return entt::to_entity(scene.sceneRegistry, component);
        }

        SystemPool &GetSystems();
        void LoadModule(const std::string &path);
        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void Assign(Entity entity, const std::string &name);
        void Remove(Entity entity, const std::string &name);
    };
}