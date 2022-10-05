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

#include <entt/entt.hpp>

#include <Core/Scene.h>
#include <Core/Macro.h>

namespace DT
{
    enum RegisterAction
    {
        AddSystem,
        Assign,
        Remove
    };

    class Component;
    typedef Component *(*RegisterFunc)(Entity, Scene *, bool, RegisterAction);

    class Entity
    {
    public:
        entt::entity handle;
        std::string name;
        Scene *scene;

        Entity();
        Entity(entt::entity entityHandle, Scene *scene);

        operator entt::entity() const { return handle; }
        operator bool() const { return handle != entt::null; }

        template <typename T>
        bool Has()
        {
            return scene->sceneRegistry.any_of<T>(handle);
        }

        template <typename T, typename... Args>
        T &Assign(Args &&...args)
        {
            DT_ASSERT(!Has<T>(), "Entity already has component.");

            T &component = scene->sceneRegistry.emplace<T>(handle, std::forward<Args>(args)...);
            
            scene->systems.insert(T::System);
            component.entity = *this;
            component.engine = scene->engine;

            if (scene->initializedComponents)
                component.Init();
            
            return component;
        }

        Component *Assign(const std::string &name)
        {
#ifdef _WIN32
            RegisterFunc registerFunc = (RegisterFunc)GetProcAddress(scene->gameModule, ("Register" + name).c_str());
#endif
#ifdef __linux__
            AssignFunc assignFunc = (AssignFunc)dlsym(scene->gameModule, ("Register" + name).c_str());
#endif
            if (!registerFunc)
            {
                std::cout << "Failed to get REGISTER(" << name << ") function from Game Module." << std::endl;
            }

            Component *component = (*registerFunc)(*this, scene, scene->initializedComponents, RegisterAction::Assign);
            
            (*registerFunc)(*this, scene, false, RegisterAction::AddSystem);

            return component;
        }

        template <typename T, typename... Args>
        T &Require(Args &&...args)
        {
            if (Has<T>())
                return Get<T>();

            return Assign<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        T &Get()
        {
            DT_ASSERT(Has<T>(), "Entity does not have component.");

            return scene->sceneRegistry.get<T>(handle);
        }

        template <typename T>
        void Remove()
        {
            DT_ASSERT(Has<T>(), "Entity does not have component.");

            scene->sceneRegistry.get<T>(handle).Destroy();
            scene->sceneRegistry.remove<T>(handle);
        }

        void Remove(const std::string &name)
        {
#ifdef _WIN32
            RegisterFunc assignFunc = (RegisterFunc)GetProcAddress(scene->gameModule, ("Register" + name).c_str());
#endif
#ifdef __linux__
            AssignFunc assignFunc = (AssignFunc)dlsym(scene->gameModule, ("Register" + name).c_str());
#endif
            if (!assignFunc)
            {
                std::cout << "Failed to get REGISTER(" << name << ") function from Game Module." << std::endl;
            }

            (*assignFunc)(*this, scene, false, RegisterAction::Remove);
        }

        template <typename T>
        static Entity From(T &component, Scene *scene)
        {
            return Entity(entt::to_entity(scene->sceneRegistry, component), scene);
        }

        bool operator==(const Entity &other);
    };
}