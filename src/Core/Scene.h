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

#include <Components/Component.h>
#include <Core/Macro.h>

namespace DT
{
    class Entity;

    class Scene
    {
    public:
        entt::registry sceneRegistry;
        static inline Scene *activeScene;
        std::function<void(Scene &)> tickFunction;

        bool initCalled = 0;

        Scene(std::function<void(Scene &)> function);

        void Init();
        void Tick();

        // Defined in Entity.cpp
        Entity CreateEntity();
        // Defined in Entity.cpp
        void DestroyEntity(Entity entity);

        template <typename T>
        void Call()
        {
            entt::view view = sceneRegistry.view<T>();

            for (auto entity : view)
            {
                if (!initCalled)
                    view.template get<T>(entity).Init();
                else
                    view.template get<T>(entity).Tick();
            }
        }
    };
}