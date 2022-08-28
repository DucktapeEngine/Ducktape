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

namespace DT
{
    unsigned int TextureFromFile(const std::string &path, const std::string &directory, bool gamma = false);

    class ModelRenderer : public Component
    {
    public:
        std::vector<Texture> texturesLoaded;
        std::vector<Mesh> meshes;
        std::string path = "../resources/models/backpack/backpack.obj";
        bool gammaCorrection;
        bool loaded = false;
        Transform *transform;
        std::string directory;

        void Init();
        void Tick();
        void LoadModel(std::string const &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}