#pragma once

#include <filesystem>

#include <Core/ImGui.h>
#include <Panels/Panel.h>
#include <Panels/ResourceImporter.h>
#include <Renderer/Texture.h>
#include <Core/Platform.h>
#include <Core/EventHandler.h>
#include <Panels/ResourceInterface.h>

namespace DT
{
    class ResourceBrowserPanel : public Panel, public EventHandler
    {
    protected:
        std::filesystem::path currentDir;
        std::filesystem::path rootDir;
        unsigned int folderIconID;
        ImGuiTextFilter filter;
        // Switches to column layout when item size is larger than this value
        const float columnSwitchSize = 24.0f;

        void RenderImGuiWindow();
        void RenderDirectoryItem(std::filesystem::directory_entry directoryEntry, int &itemSize);
        void HandleItemSelected(bool isDir, std::filesystem::path path);
        void HandleItemDoubleClicked(bool isDir, std::filesystem::path path);

    public:
        std::filesystem::path selectedItemPath;

        enum Events
        {
            OnItemSelect
        };

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
    };
}