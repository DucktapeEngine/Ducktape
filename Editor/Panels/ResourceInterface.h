#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <json/json.hpp>
using json = nlohmann::json;

#include <Renderer/Texture.h>
#include <Renderer/Material.h>
#include <Core/Macro.h>
#include <Core/Resource.h>
#include <Core/ImGui.h>
#include <Renderer/Mesh.h>
#include <Scene/Entity.h>
#include <Core/ResourceManager.h>

namespace DT
{
    class Interface
    {
    public:
        unsigned int iconId = 0;

        virtual void Init() {}
        virtual void Inspect() {}
        virtual void Import(RID rid) {}
        virtual void OpenInspect(RID rid) {}
        virtual void CloseInspect() {}
    };

    namespace ResourceInterface
    {
        inline std::unordered_map<std::string, Interface *> interfaces;

        template <typename T, class... Args>
        void RegisterInterface(const Args &...args)
        {
            std::vector<std::string> extensions = {args...};

            Interface *interface = new T();
            interface->Init();

            for (unsigned i = 0; i < extensions.size(); i++)
                interfaces[extensions[i]] = interface;
        }

        Interface *GetInterface(const std::string &extension);
        bool HasInterface(const std::string &extension);
        void AddDefault();

        unsigned int GetIcon(const std::string &extension);
    }

    class MaterialInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Material> openedMaterial;
        std::string filename = "Unnamed Material";

        void Init() override;
        void Inspect() override;
        void OpenInspect(RID rid) override;
        void CloseInspect() override;
    };

    class TextureInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Texture> openedTexture;
        std::string filename = "Unnamed Texture";

        void Init() override;
        void Inspect() override;
        void OpenInspect(RID rid) override;
        void CloseInspect() override;
    };

    class MeshInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Mesh> openedMesh;
        std::string filename = "Unnamed Mesh";

        void Init() override;
        void Inspect() override;
        void OpenInspect(RID rid) override;
        void CloseInspect() override;
    };

    class ModelImporter
    {
    public:
        std::filesystem::path directory;
        std::string modelName;

        ModelImporter(std::filesystem::path path);

        void ProcessNode(aiNode *node, const aiScene *scene);
        void ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<RID> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType);
    };

    class ModelInterface : public Interface
    {
    public:
        std::string filename = "Unnamed Model";

        void Init() override;
        void OpenInspect(RID rid) override;
        void Inspect() override;
        void Import(RID rid) override;
    };

    class MarkdownInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        std::string filename = "Unnamed Mesh";
        std::string data;

        void Init() override;
        void Inspect() override;
        void OpenInspect(RID rid) override;
    };
}