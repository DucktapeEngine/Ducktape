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

#include <functional>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <entt/entt.hpp>

#include <Core/Scene.h>
#include <Core/Macro.h>

namespace DT
{
    class Entity
    {
    public:
        entt::entity handle;
        std::string name;
        Scene *scene;

        Entity();
        Entity(entt::entity entityHandle, Scene *scene) : handle(entityHandle), scene(scene) {}

        operator entt::entity() const { return handle; }
        operator bool() const { return handle != entt::null; }

        template <typename T>
        bool HasComponent()
        {
            return scene->sceneRegistry.any_of<T>(handle);
        }

        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            DT_ASSERT(!HasComponent<T>(), "Entity already has component.");

            T &component = scene->sceneRegistry.emplace<T>(handle, std::forward<Args>(args)...);
            return component;
        }

        template <typename T, typename... Args>
        T &RequireComponent(Args &&...args)
        {
            if (HasComponent<T>())
                return GetComponent<T>();

            return AddComponent<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        T &GetComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");

            return scene->sceneRegistry.get<T>(handle);
        }

        template <typename T>
        void RemoveComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");

            scene->sceneRegistry.get<T>(handle).OnDestroy();
            scene->sceneRegistry.remove<T>(handle);
        }

        template <typename T>
        static Entity FromComponent(T &component)
        {
            return FromComponent<T>(component, Scene::activeScene);
        }

        template <typename T>
        static Entity FromComponent(T &component, Scene *scene)
        {
            return Entity(entt::to_entity(scene->sceneRegistry, component), scene);
        }
    };
}