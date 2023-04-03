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

#include <Core/Platform.h>
#include <Scene/System.h>
#include <Scene/Entity.h>
#include <Core/Configuration.h>

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
    typedef void (*RegisterFunc)(Entity, Scene *, RegisterAction);

    class Scene
    {
    protected:
        class SystemPool
        {
        public:
            char *pData{nullptr};
            unsigned int noAllocatedSystems = 0;

            SystemPool()
            {
                pData = new char[sizeof(System) * MAX_SYSTEMS];
            }

            ~SystemPool()
            {
                delete[] pData;
            }

            inline void *Get(size_t index)
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

                bool operator==(const Iterator &other) const
                {
                    return idx == other.idx;
                }

                bool operator!=(const Iterator &other) const
                {
                    return idx != other.idx;
                }

                Iterator &operator++()
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
                return Iterator(this, noAllocatedSystems);
            }
        };

    public:
        SystemPool systems;

        static inline std::set<Scene *> scenes;

        entt::registry registry;            /// @brief Registry of all the components and entities in the scene
        Camera *activeCamera = nullptr;     /// @brief Active camera of the scene
        Platform::Module gameModule;        /// @brief Dll containing the game
        Entity selectedEntity = entt::null; /// @brief FIXME: Find cause of buggy identifier and why we have to pass null

        Scene(Configuration &config);
        ~Scene();

        static Scene *GetScene(entt::registry &registry);

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
            return registry.any_of<T>(entity);
        }

        template <typename T>
        T &Assign(Entity entity)
        {
            if (Has<T>(entity))
                return *Get<T>(entity);

            return registry.emplace<T>(entity);
        }

        template <typename T>
        T *Get(Entity entity)
        {
            if (Has<T>(entity))
                return &registry.get<T>(entity);
            else
                return nullptr;
        }

        template <typename T>
        void Remove(Entity entity)
        {
            if (Has<T>(entity))
            {
                // sceneRegistry.get<T>(entity).Destroy(); //TOFIX: Destroy currently not called
                registry.remove<T>(entity);
            }
        }

        template <typename... Components>
        auto View()
        {
            return registry.view<Components...>();
        }

        template <typename T>
        static Entity From(T &component, Scene &scene)
        {
            return entt::to_entity(scene.registry, component);
        }

        void LoadModule(std::filesystem::path path);
        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void Assign(Entity entity, const std::string &name);
        void Remove(Entity entity, const std::string &name);
    };
}