#pragma once

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

#include <Core/ImGui.h>
#include <Panels/Panel.h>
#include <Renderer/Texture.h>

namespace DT
{
    class ResourceBrowserPanel : public Panel
    {
    private:
        std::filesystem::path currentDir;
        std::filesystem::path rootDir;
        unsigned int folderIconID;
        ImGuiTextFilter Filter;
        // Switches to column layout when item size is larger than this value
        const float columnSwitchSize = 24.0f;
        void RenderImGuiWindow();
        void RenderDirectoryItem(std::filesystem::directory_entry directoryEntry, int &itemSize);
        void OnItemDoubleClicked(bool isDir, std::filesystem::path path);
        unsigned int GetKnownIconID(std::filesystem::path path);

    public:
        void Start() override;
        void Update(Engine &engine) override;
        void Destroy() override;
    };
}