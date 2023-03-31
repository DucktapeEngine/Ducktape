/*
Ducktape | An open source C++ 2D & 3D game ctx that focuses on being fast, and powerful.
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

#include <Core/Platform.h>
#include <Scene/Entity.h>
#include <Core/Context.h>

#define REGISTER(component)                                                                            \
    DT_EXPORT void Register##component(DT::Entity entity, DT::Scene *scene, DT::RegisterAction action) \
    {                                                                                                  \
        switch (action)                                                                                \
        {                                                                                              \
        case DT::RegisterAction::Assign:                                                               \
            scene->Assign<component>(entity);                                                          \
            break;                                                                                     \
        case DT::RegisterAction::Remove:                                                               \
            scene->Remove<component>(entity);                                                          \
            break;                                                                                     \
        }                                                                                              \
    }

namespace DT
{
    const int MAX_SYSTEMS = 64;

    class Scene;

    class System
    {
    public:
        virtual void Init(Scene *scene, const Context &ctx) {}
        virtual void Tick(Scene *scene, const Context &ctx) {}
        virtual void SceneView(Scene *scene, const Context &ctx) {}
        virtual void Destroy(Scene *scene, const Context &ctx) {}
        virtual void Inspector(Scene *scene, const Context &ctx) {}
        virtual void Serialize(Scene *scene, const Context &ctx, Entity entity) {}
    };
}