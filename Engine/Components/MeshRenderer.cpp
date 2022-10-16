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
    void MeshRendererSystem::Init(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<MeshRenderer>())
        {
            MeshRenderer &mr = scene.Get<MeshRenderer>(entity);

            mr.transform = &scene.Require<Transform>(entity);

            if (mr.shader == nullptr)
                mr.shader = &engine.renderer.defaultShader;

            mr.mesh.Setup();
        }
    }

    void MeshRendererSystem::Tick(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<MeshRenderer>())
        {
            MeshRenderer &mr = scene.Get<MeshRenderer>(entity);

            mr.shader->Use();
            mr.shader->SetMat4("model", mr.transform->GetModelMatrix());
            mr.shader->SetVec3("material.color", mr.material.color);
            mr.shader->SetFloat("material.shininess", mr.material.shininess);

            mr.mesh.Draw(*mr.shader);
        }
    }

    void MeshRendererSystem::SceneView(Scene &scene, Engine &engine)
    {
        Tick(scene, engine);
    }

    void MeshRendererSystem::Inspector(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<MeshRenderer>())
        {
            if (scene.selectedEntity != entity)
                continue;

            MeshRenderer &mr = scene.Get<MeshRenderer>(entity);

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                ImGui::Mesh("mesh", &mr.mesh);
                ImGui::Material("material", &mr.material);
            }
        }
    }
}