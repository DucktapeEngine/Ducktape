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

#include <Renderer/Mesh.h>
#include <Core/ImGui.h>
#include <Scene/Entity.h>
#include <Renderer/Material.h>
#include <Components/Transform.h>
#include <Core/Serialization.h>
#include <Core/Resource.h>
#include <Scene/SceneManager.h>

#include <Components/MeshRenderer.h>

namespace DT
{
    void MeshRendererSystem::Init(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<MeshRenderer>())
        {
            MeshRenderer *mr = ctx.sceneManager->GetActiveScene().Get<MeshRenderer>(entity);

            mr->transform = &ctx.sceneManager->GetActiveScene().Assign<Transform>(entity);

            mr->mesh.Reload(ctx);
            mr->mesh.data->Setup();
        }
    }

    void MeshRendererSystem::Tick(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<MeshRenderer>())
        {
            MeshRenderer *mr = ctx.sceneManager->GetActiveScene().Get<MeshRenderer>(entity);

            mr->mesh.data->Draw(mr->transform->GetModelMatrix(), *ctx.renderer);

            Transform *transform = ctx.sceneManager->GetActiveScene().Get<Transform>(entity);
            transform->translation += glm::vec3(1.f);
        }
    }

    void MeshRendererSystem::SceneView(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<MeshRenderer>())
        {
            MeshRenderer *mr = ctx.sceneManager->GetActiveScene().Get<MeshRenderer>(entity);

            mr->mesh.data->Draw(mr->transform->GetModelMatrix(), *ctx.renderer);
        }
    }

    void MeshRendererSystem::Serialize(ContextPtr &ctx, Entity entity)
    {
        ctx.sceneManager->GetActiveScene().SerializeComponent<MeshRenderer>("MeshRenderer", entity, ctx.sceneManager->GetActiveScene());
    }

    void MeshRendererSystem::Inspector(ContextPtr &ctx, Entity selectedEntity)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<MeshRenderer>())
        {
            if (selectedEntity != entity)
                continue;

            MeshRenderer *mr = ctx.sceneManager->GetActiveScene().Get<MeshRenderer>(entity);

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                ImGui::Resource("mesh", &mr->mesh, ctx);
                // ImGui::Resource("material", mr->material);
            }
        }
    }
}