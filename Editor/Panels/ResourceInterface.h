#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <Renderer/Texture.h>
#include <Renderer/Material.h>
#include <Core/Macro.h>
#include <Core/Resource.h>
#include <Core/ImGui.h>

namespace DT
{
    class Interface
    {
    public:
        unsigned int iconId = 0;

        virtual void Init() {}
        virtual void Inspect() {}
        virtual void Import() {}
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