#include <Panels/ResourceInterface.h>

namespace DT
{
    void MaterialInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "material.png"))->id;
    }

    void MaterialInterface::OpenInspect(RID rid)
    {
        openedMaterial.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MaterialInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Material");

        ImGui::Separator();

        ImGui::Color("diffuse color", &openedMaterial.Data()->diffuseColor);
        ImGui::Color("specular color", &openedMaterial.Data()->specularColor);
        ImGui::Color("ambient color", &openedMaterial.Data()->ambientColor);
        ImGui::DragFloat("shininess", &openedMaterial.Data()->shininess);
        ImGui::Resource("texture", &openedMaterial.Data()->texture);
        // ImGui:: something for texture type
        ImGui::Resource("shader", &openedMaterial.Data()->shader);
    }

    void MaterialInterface::CloseInspect()
    {
        openedMaterial.Save();
    }

    void TextureInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "image.png"))->id;
    }

    void TextureInterface::OpenInspect(RID rid)
    {
        openedTexture.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void TextureInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Texture");

        ImGui::Separator();

        ImGui::Image((ImTextureID)(uintptr_t)openedTexture.Data()->id, ImVec2(ImGui::GetWindowContentRegionWidth(), openedTexture.Data()->height * (ImGui::GetWindowContentRegionWidth() / openedTexture.Data()->width)), ImVec2(0, 1), ImVec2(1, 0));
    }

    void TextureInterface::CloseInspect()
    {
        openedTexture.Save();
    }

    void MeshInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "model.png"))->id;
    }

    void MeshInterface::OpenInspect(RID rid)
    {
        openedMesh.Load(rid);
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MeshInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Mesh");

        ImGui::Separator();

        ImGui::Text("materials");
        for (int i = 0; i < openedMesh.Data()->materials.size(); i++)
            ImGui::Resource("materials##" + std::to_string(i), &openedMesh.Data()->materials[i]);
    }

    void MeshInterface::CloseInspect()
    {
        openedMesh.Save();
    }

    void MarkdownInterface::Init()
    {
        iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "markdown.png"))->id;
    }

    void MarkdownInterface::OpenInspect(RID rid)
    {
        std::ifstream in("file.txt");
        std::stringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();
        filename = ResourceManager::GetPath(rid).filename().string();
    }

    void MarkdownInterface::Inspect()
    {
        ImGui::Text(filename.c_str());
        ImGui::TextDisabled("Markdown");

        ImGui::Separator();

        ImGui::TextDisabled("Markdown Viewer yet to be implemented.");
    }

    Interface *ResourceInterface::GetInterface(const std::string &extension)
    {
        if (!HasInterface(extension))
            return nullptr;
        return interfaces[extension];
    }

    bool ResourceInterface::HasInterface(const std::string &extension)
    {
        return interfaces.find(extension) != interfaces.end();
    }

    unsigned int ResourceInterface::GetIcon(const std::string &extension)
    {
        unsigned int iconId = 0;
        Interface *interface = ResourceInterface::GetInterface(extension);
        if (interface != nullptr)
            iconId = interface->iconId;
        if (iconId == 0)
            iconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "ResourceBrowser" / "file.png"))->id;
        return iconId;
    }

    void ResourceInterface::AddDefault()
    {
        RegisterInterface<MaterialInterface>(".mtl", ".dtmaterial");
        RegisterInterface<TextureInterface>(".jpg", ".png", ".jpeg");
        RegisterInterface<MeshInterface>(".obj", ".fbx", ".dtmesh");
        RegisterInterface<MarkdownInterface>(".md");
    }
}