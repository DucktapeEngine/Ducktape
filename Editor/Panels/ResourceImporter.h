#pragma once

#include <string>
#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <json/json.hpp>
using json = nlohmann::json;

#include <Renderer/Mesh.h>
#include <Scene/Entity.h>
#include <Renderer/Texture.h>
#include <Core/ResourceManager.h>

namespace DT
{
    typedef void (*Importer)(const std::filesystem::path &);

    namespace ResourceImporter
    {
        inline std::unordered_map<std::string, Importer> importers;

        void Reimport(const std::filesystem::path &path);
        void AddImporter(std::string extension, Importer importer);
    }

    class ImportModel
    {
    public:
        std::filesystem::path directory;
        std::string modelName;

        ImportModel(std::filesystem::path path);

        void ProcessNode(aiNode *node, const aiScene *scene);
        void ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<RID> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType);
    };

    void ModelImporter(const std::filesystem::path &path);
}