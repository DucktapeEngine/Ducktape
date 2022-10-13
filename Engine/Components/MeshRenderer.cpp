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

#include <Core/Macro.h>
#include <Components/MeshRenderer.h>

namespace DT
{
    void MeshRenderer::Init()
    {
        transform = &entity.Require<Transform>();

        if (shader == nullptr)
            shader = &engine->renderer.defaultShader;

        mesh.Setup();
    }

    void MeshRenderer::Tick()
    {
        shader->Use();
        shader->SetMat4("model", transform->GetModelMatrix());
        shader->SetVec3("material.color", material.color);
        shader->SetFloat("material.shininess", material.shininess);

        mesh.Draw(*shader);
    }

    void MeshRenderer::Inspector()
    {
        COMPONENT("MeshRenderer");

        PROPERTY("shininess", &material.shininess);
        PROPERTY("color", &material.color);
    }

    void MeshRenderer::SceneView(bool selected)
    {
        UNUSED(selected);
        Tick();
    }

    void Serialize(Serializer &serializer, MeshRenderer &object)
    {
        serializer & object.mesh & object.material;
    }
}
