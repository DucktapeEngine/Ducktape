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

#include <string>

#include <entt/entt.hpp>

#include <Components/Component.h>

namespace Ducktape
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