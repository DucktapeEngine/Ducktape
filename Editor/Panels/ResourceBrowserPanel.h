#pragma once

#include <filesystem>
#include <fstream>

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
    public:
        void Start() override;
        void Update(Engine &engine) override;
        void Destroy() override;
        const char* GetWindowName() override;
    private:
        enum FileCreateType
        {
            FileCreateType_File,
            FileCreateType_Folder
        };
        enum FileAction
        {
            FileAction_None,
            FileAction_Create,
            FileAction_Rename,
            FileAction_Delete
        };

        const char* windowName = "Resource Browser";
        std::filesystem::path currentDir; /// @brief Current directory of user.
        std::filesystem::path rootDir; /// @brief Root resources directory of Ducktape.
        std::filesystem::path resourceDir; /// @brief Resource directory such as icons being used for.
        unsigned int folderIconID; /// @brief Ready to use initialized folder icon ID.
        unsigned int fileIconID; /// @brief Ready to use initialized file icon ID.
        ImGuiTextFilter Filter; /// @brief Filtering of files.
        // Switches to column layout when item size is larger than this value
        const float columnSwitchSize = 24.0f; /// @brief If item size is set larger than this value, resource browser will switch to column layout.
        FileAction fileAction = FileAction_None; /// @brief Flag for user actions.
        FileCreateType creatingFileType; /// @brief The file type user trying to create.
        std::filesystem::path selectedFile = ""; /// @brief Holds selected file for actions such as delete / rename that needs confirm.
        void RenderImGuiWindow();
        void RenderDirectoryItem(std::filesystem::directory_entry directoryEntry, float itemSize);
        void RenderEditItem(float itemSize);
        void OnItemDoubleClicked(bool isDir, std::filesystem::path path);
        unsigned int GetKnownIconID(std::filesystem::path path);
    };
}