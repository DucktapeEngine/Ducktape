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
#include <Scene/SceneManager.h>
#include <Core/Serialization.h>

namespace DT
{
    template <typename T>
    class GenericSystem : public System
    {
    protected:
        const std::string componentName;

        HAS_METHOD_DECL(Init);
        HAS_METHOD_DECL(Tick);
        HAS_METHOD_DECL(SceneView);
        HAS_METHOD_DECL(Destroy);
        HAS_METHOD_DECL(Serialize);
        HAS_METHOD_DECL(Inspector);

    public:
        GenericSystem(const std::string &compName) : componentName(compName) {}

        void Init(ContextPtr &ctx) override
        {
            if constexpr (HasInit<T>::value)
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                    ctx.sceneManager->GetActiveScene().Get<T>(entity)->Init(entity, ctx);
        }

        void Tick(ContextPtr &ctx) override
        {
            if constexpr (HasTick<T>::value)
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                    ctx.sceneManager->GetActiveScene().Get<T>(entity)->Tick(entity, ctx);
        }

        void SceneView(ContextPtr &ctx) override
        {
            if constexpr (HasSceneView<T>::value)
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                    ctx.sceneManager->GetActiveScene().Get<T>(entity)->SceneView(entity, ctx);
        }

        void Destroy(ContextPtr &ctx) override
        {
            if constexpr (HasDestroy<T>::value)
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                    ctx.sceneManager->GetActiveScene().Get<T>(entity)->Destroy(entity, ctx);
        }

        void Serialize(ContextPtr &ctx, Entity entity) override
        {
            if constexpr (HasSerialize<T>::value)
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                    ctx.sceneManager->GetActiveScene().SerializeComponent<T>(componentName, entity, ctx.sceneManager->GetActiveScene());
        }

        void Inspector(ContextPtr &ctx, Entity selectedEntity) override
        {
            if constexpr (HasInspector<T>::value)
            {
                for (Entity entity : ctx.sceneManager->GetActiveScene().View<T>())
                {
                    if (entity != selectedEntity)
                        continue;

                    ctx.sceneManager->GetActiveScene().Get<T>(entity)->Inspector(entity, ctx, selectedEntity);
                }
            }
        }
    };
}