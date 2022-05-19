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

#pragma once

#include <functional>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <entt/entt.hpp>

#include <Core/Scene.h>
#include <Core/Macro.h>

namespace Ducktape
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