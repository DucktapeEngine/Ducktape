/*
Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
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

#include <Scene/System.h>

// Source: https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
#define HAS_METHOD_DECL(methodName)\
    template <typename CheckType>\
    class Has ## methodName\
    {\
        typedef char One;\
        struct Two {char x[2];};\
        template <typename C> static One Test( decltype(&C::methodName));\
        template <typename C> static Two Test(...);\
    public:\
        enum {value = sizeof(Test<CheckType>(0)) == sizeof(char)};\
    };

namespace DT
{
    template <typename T>
    class GenericSystem : public System
    {
    private:
        HAS_METHOD_DECL(Init);
        HAS_METHOD_DECL(Tick);
        HAS_METHOD_DECL(SceneView);
        HAS_METHOD_DECL(Destroy);
        HAS_METHOD_DECL(Serialize);
        HAS_METHOD_DECL(Inspector);

    public:
        void Init(Scene &scene, Engine &engine) override
        {
            if constexpr (HasInit<T>::value)
                for (Entity entity : scene.View<T>())
                    scene.Get<T>(entity).Init(entity, scene, engine);
        }

        void Tick(Scene &scene, Engine &engine) override
        {
            if constexpr (HasTick<T>::value)
                for (Entity entity : scene.View<T>())
                    scene.Get<T>(entity).Tick(entity, scene, engine);
        }

        void SceneView(Scene &scene, Engine &engine) override
        {
            if constexpr (HasSceneView<T>::value)
                for (Entity entity : scene.View<T>())
                    scene.Get<T>(entity).SceneView(entity, scene, engine);
        }

        void Destroy(Scene &scene, Engine &engine) override
        {
            if constexpr (HasDestroy<T>::value)
                for (Entity entity : scene.View<T>())
                    scene.Get<T>(entity).Destroy(entity, scene, engine);
        }

        void Serialize(Scene &scene, Engine &engine) override
        {
            // if constexpr (HasSerialize<T>::value)
            //     for (Entity entity : scene.View<T>())
            //         Serialize(engine.serializer, );
        }

        void Inspector(Scene &scene, Engine &engine) override
        {
            if constexpr (HasInspector<T>::value)
                for (Entity entity : scene.View<T>())
                    scene.Get<T>(entity).Inspector(entity, scene, engine);
        }
    };
}