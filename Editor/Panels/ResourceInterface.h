#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Renderer/Texture.h>
#include <Renderer/Material.h>
#include <Core/Serialization.h>
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

        virtual void Init(ContextPtr& ctx) {}
        virtual void Inspect(ContextPtr& ctx) {}
        virtual void Import(RID rid, ContextPtr &ctx) {}
        virtual void OpenInspect(RID rid, ContextPtr& ctx) {}
        virtual void CloseInspect(ContextPtr& ctx) {}
    };

    namespace ResourceInterface
    {
        inline std::unordered_map<std::string, Interface *> interfaces;

        template <typename T>
        void RegisterInterface(std::vector<std::string> extensions, ContextPtr &ctx)
        {
            Interface *_interface = new Interface();
            _interface->Init(ctx);

            for (unsigned i = 0; i < extensions.size(); i++)
                interfaces[extensions[i]] = _interface;
        }

        Interface *GetInterface(const std::string &extension);
        bool HasInterface(const std::string &extension);
        void AddDefault(ContextPtr &ctx);

        unsigned int GetIcon(const std::string &extension, ContextPtr &ctx);
    }

    class MaterialInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Material> openedMaterial;
        std::string filename = "Unnamed Material";

        void Init(ContextPtr &ctx) override;
        void Inspect(ContextPtr &ctx) override;
        void OpenInspect(RID rid, ContextPtr& ctx) override;
        void CloseInspect(ContextPtr &ctx) override;
    };

    class TextureInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Texture> openedTexture;
        std::string filename = "Unnamed Texture";

        void Init(ContextPtr &ctx) override;
        void Inspect(ContextPtr &ctx) override;
        void OpenInspect(RID rid, ContextPtr& ctx) override;
        void CloseInspect(ContextPtr &ctx) override;
    };

    class MeshInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        Resource<Mesh> openedMesh;
        std::string filename = "Unnamed Mesh";

        void Init(ContextPtr &ctx) override;
        void Inspect(ContextPtr &ctx) override;
        void OpenInspect(RID rid, ContextPtr& ctx) override;
        void CloseInspect(ContextPtr &ctx) override;
    };

    class ModelImporter
    {
    public:
        std::filesystem::path directory;
        std::string modelName;

        ModelImporter(std::filesystem::path path, ContextPtr &ctx);

        void ProcessNode(aiNode *node, const aiScene *scene, ContextPtr &ctx);
        void ProcessMesh(aiMesh *mesh, const aiScene *scene, ContextPtr &ctx);
        std::vector<RID> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, Texture::Type textureType, ContextPtr &ctx);
    };

    class ModelInterface : public Interface
    {
    public:
        std::string filename = "Unnamed Model";

        void Init(ContextPtr &ctx) override;
        void OpenInspect(RID rid, ContextPtr& ctx) override;
        void Inspect(ContextPtr &ctx) override;
        void Import(RID rid, ContextPtr &ctx) override;
    };

    class MarkdownInterface : public Interface
    {
    public:
        std::filesystem::path openedPath;
        std::string filename = "Unnamed Mesh";
        std::string data;

        void Init(ContextPtr &ctx) override;
        void Inspect(ContextPtr &ctx) override;
        void OpenInspect(RID rid, ContextPtr& ctx) override;
    };
}