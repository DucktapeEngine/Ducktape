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

#include <vector>
#include <string>

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Renderer/Mesh.h>
#include <Components/Transform.h>
#include <Core/Debug.h>
#include <Core/Entity.h>
using namespace DT;

class ModelRenderer : public Component
{
public:
    std::vector<Texture> texturesLoaded;
    std::vector<Mesh> meshes;
    std::string path = "../Resources/Models/backpack/backpack.obj";
    bool gammaCorrection;
    bool loaded = false;
    Transform *transform;
    std::string directory;

    void Init()
    {
        transform = &Entity::FromComponent(*(NativeScriptComponent *)holderComponent, engine->activeScene).RequireComponent<Transform>();

        LoadModel(path);
    }

    void Tick()
    {
        if (!loaded)
            return;

        engine->renderer.defaultShader.Use();
        engine->renderer.defaultShader.SetMat4("model", transform->GetModelMatrix());

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(engine->renderer.defaultShader);
    }

    void LoadModel(std::string const &path)
    {
        if (path == "")
            return;
    }
};

extern "C" __declspec(dllexport) Component *CreateModule()
{
    return new ModelRenderer();
}