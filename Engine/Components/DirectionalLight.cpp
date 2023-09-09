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
#include <Scene/System.h>
#include <Core/Serialization.h>
#include <Renderer/Renderer.h>
#include <Core/Resource.h>
#include <Core/ImGui.h>
#include <Scene/SceneManager.h>

#include <Components/DirectionalLight.h>

namespace DT
{
    void DirectionalLightSystem::Init(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<DirectionalLight>())
        {
            DirectionalLight *dl = ctx.sceneManager->GetActiveScene().Get<DirectionalLight>(entity);

            dl->shader.Load(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Default.glsl"), ctx);
            dl->transform = &ctx.sceneManager->GetActiveScene().Assign<Transform>(entity);

            if (ctx.renderer->GetFreeDirectionalLightSpot(&dl->lightSpot) == false)
            {
                std::cerr << "DirectionalLight: No free light spots.\n";
                continue;
            }

            dl->propertyString = "directionalLights[" + std::to_string(dl->lightSpot) + "].";
            dl->shader.data->Use();
            dl->shader.data->SetBool(dl->propertyString + "enabled", true);
        }
    }

    void DirectionalLightSystem::Tick(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<DirectionalLight>())
        {
            DirectionalLight *dl = ctx.sceneManager->GetActiveScene().Get<DirectionalLight>(entity);

            if (dl->lightSpot == NAN)
                continue;

            dl->shader.data->Use();
            dl->shader.data->SetVec3(dl->propertyString + "direction", dl->transform->Forward());
            dl->shader.data->SetVec3(dl->propertyString + "ambient", dl->color * dl->intensity);
            dl->shader.data->SetVec3(dl->propertyString + "diffuse", dl->color * dl->intensity);
            dl->shader.data->SetVec3(dl->propertyString + "specular", dl->color * dl->intensity);
        }
    }

    void DirectionalLightSystem::Destroy(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<DirectionalLight>())
        {
            DirectionalLight *dl = ctx.sceneManager->GetActiveScene().Get<DirectionalLight>(entity);

            ctx.renderer->UnoccupyDirectionalLightSpot(dl->lightSpot);
            dl->shader.data->SetBool(dl->propertyString + "enabled", true);
        }
    }

    void DirectionalLightSystem::SceneView(ContextPtr &ctx)
    {
        Tick(ctx);
    }

    void DirectionalLightSystem::Serialize(ContextPtr &ctx, Entity entity)
    {
        ctx.sceneManager->GetActiveScene().SerializeComponent<DirectionalLight>("DirectionalLight", entity, ctx.sceneManager->GetActiveScene());
    }

    void DirectionalLightSystem::Inspector(ContextPtr &ctx, Entity selectedEntity)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<DirectionalLight>())
        {
            if (selectedEntity != entity)
                continue;

            DirectionalLight *dl = ctx.sceneManager->GetActiveScene().Get<DirectionalLight>(entity);

            if (ImGui::CollapsingHeader("Directional Light"))
            {
                ImGui::DragFloat("intensity", &dl->intensity, 0.1f, 0.f, 5.f);
                ImGui::ColorEdit3("color", &dl->color.x);
            }
        }
    }
}