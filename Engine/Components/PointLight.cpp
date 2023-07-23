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

#include <Renderer/Shader.h>
#include <Components/Transform.h>
#include <Scene/Scene.h>
#include <Core/Serialization.h>
#include <Renderer/Renderer.h>
#include <Core/Resource.h>
#include <Core/ImGui.h>
#include <Components/PointLight.h>

namespace DT
{
    void PointLightSystem::Init(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<PointLight>())
        {
            PointLight *pl = ctx.sceneManager->GetActiveScene().Get<PointLight>(entity);

            pl->shader.Load(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Default.glsl"), ctx);
            pl->transform = &ctx.sceneManager->GetActiveScene().Assign<Transform>(entity);

            if (ctx.renderer->GetFreePointLightSpot(&pl->lightSpot) == false)
            {
                std::cerr << "PointLight: No free light spots.\n";
            }

            pl->propertyString = "pointLights[" + std::to_string(pl->lightSpot) + "].";

            pl->shader.data->Use();
            pl->shader.data->SetFloat(pl->propertyString + "constant", 1.0f);
            pl->shader.data->SetFloat(pl->propertyString + "quadratic", 1.0f);
            pl->shader.data->SetBool(pl->propertyString + "enabled", true);
        }
    }

    void PointLightSystem::Tick(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<PointLight>())
        {
            PointLight *pl = ctx.sceneManager->GetActiveScene().Get<PointLight>(entity);

            if (pl->lightSpot == NAN)
                return;

            pl->shader.data->Use();
            pl->shader.data->SetVec3(pl->propertyString + "position", pl->transform->translation);

            pl->shader.data->SetFloat(pl->propertyString + "linear", pl->intensity);
            pl->shader.data->SetVec3(pl->propertyString + "ambient", pl->color * pl->intensity);
            pl->shader.data->SetVec3(pl->propertyString + "diffuse", pl->color * pl->intensity);
            pl->shader.data->SetVec3(pl->propertyString + "specular", pl->color * pl->intensity);
        }
    }

    void PointLightSystem::Inspector(ContextPtr &ctx, Entity selectedEntity)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<PointLight>())
        {
            if (selectedEntity != entity)
                continue;

            PointLight *pl = ctx.sceneManager->GetActiveScene().Get<PointLight>(entity);

            if (ImGui::CollapsingHeader("Point Light"))
            {
                ImGui::DragFloat("intensity", &pl->intensity);
                ImGui::ColorEdit3("color", &pl->color.x);
            }
        }
    }

    void PointLightSystem::SceneView(ContextPtr &ctx)
    {
        Tick(ctx);
    }

    void PointLightSystem::Serialize(ContextPtr &ctx, Entity entity)
    {
        ctx.sceneManager->GetActiveScene().SerializeComponent<PointLight>("PointLight", entity, ctx.sceneManager->GetActiveScene());
    }

    void PointLightSystem::Destroy(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<PointLight>())
        {
            PointLight *pl = ctx.sceneManager->GetActiveScene().Get<PointLight>(entity);

            ctx.renderer->UnoccupyPointLightSpot(pl->lightSpot);
            pl->shader.data->SetBool(pl->propertyString + "enabled", false); // TOFIX: Move this to Renderer class
        }
    }
}