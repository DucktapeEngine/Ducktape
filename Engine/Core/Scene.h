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

#include <entt/entt.hpp>
#include <imgui/imgui.h>

namespace DT
{
    class Entity;
    class Scene;
    class Engine;

    typedef void (*System)(Scene*);

    enum CallState
    {
        EngineAssignment,
        Init,
        Tick,
        SceneView,
        Destroy
    };

    class Scene
    {
    public:
        entt::registry sceneRegistry;
        std::unordered_set<System> systems;
        CallState callState;
        Engine *engine;

        void Init(Engine *e);
        void Tick();
        void SceneView();
        void Destroy();

        template <typename T>
        void Call()
        {
            auto view = sceneRegistry.view<T>();

            for (auto entity : view)
            {
                T &component = view. template get<T>(entity);

                switch (callState)
                {
                    case CallState::EngineAssignment:
                        component.engine = engine;
                        break;
                    case CallState::Init:
                        component.Init();
                        break;
                    case CallState::Tick:
                        component.Tick();
                        break;
                    case CallState::SceneView:
                        component.SceneView();
                        break;
                    case CallState::Destroy:
                        component.Destroy();
                        break;
                }
            }            
        }

        // Defined in Entity.cpp
        Entity CreateEntity();
        // Defined in Entity.cpp
        void DestroyEntity(Entity entity);
    };
}