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

#include <Components/MeshRenderer.h>

namespace DT
{
    void MeshRendererSystem::Init(Scene *scene, const Context &ctx)
    {
        for (Entity entity : scene->View<MeshRenderer>())
        {
            MeshRenderer &mr = scene->Get<MeshRenderer>(entity);

            mr.transform = &scene->Require<Transform>(entity);

            mr.mesh.Data()->Setup();
        }
    }

    void MeshRendererSystem::Tick(Scene *scene, const Context &ctx)
    {
        for (Entity entity : scene->View<MeshRenderer>())
        {
            MeshRenderer &mr = scene->Get<MeshRenderer>(entity);

            mr.mesh.Data()->Draw(mr.transform->GetModelMatrix(), *ctx.renderer);
        }
    }

    void MeshRendererSystem::SceneView(Scene *scene, const Context &ctx)
    {
        Tick(scene, ctx);
    }

    void MeshRendererSystem::Serialize(Scene *scene, const Context &ctx)
    {
        for (Entity entity : scene->View<MeshRenderer>())
        {
            MeshRenderer &mr = scene->Get<MeshRenderer>(entity);

            ctx.serialization->SerializeComponent("MeshRenderer", mr, entity);
        }
    }

    void MeshRendererSystem::Inspector(Scene *scene, const Context &ctx)
    {
        for (Entity entity : scene->View<MeshRenderer>())
        {
            if (scene->selectedEntity != entity)
                continue;

            MeshRenderer &mr = scene->Get<MeshRenderer>(entity);

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                ImGui::Resource("mesh", &mr.mesh);
                // ImGui::Resource("material", mr.material);
            }
        }
    }
}