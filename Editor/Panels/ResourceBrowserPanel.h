#pragma once

#include <filesystem>
#include <fstream>

#include <Core/ImGui.h>
#include <Panels/Panel.h>
#include <Renderer/Texture.h>
#include <Core/Platform.h>
#include <Core/EventHandler.h>
#include <Panels/ResourceInterface.h>

namespace DT
{
    class ResourceBrowserPanel : public Panel, public EventHandler
    {
    protected:
        std::filesystem::path currentDir;  /// @brief Current directory of user.
        std::filesystem::path rootDir;     /// @brief Root resources directory of Ducktape.
        std::filesystem::path resourceDir; /// @brief Resource directory such as icons being used for.
        unsigned int folderIconId;         /// @brief Ready to use initialized folder icon ID.
        unsigned int fileIconId;           /// @brief Ready to use initialized file icon ID.
        ImGuiTextFilter filter;            /// @brief Filtering of files.

        const float columnSwitchSize = 24.0f; /// @brief If item size is set larger than this value, resource browser will switch to column layout.

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

        FileAction fileAction = FileAction_None; /// @brief Flag for user actions.
        FileCreateType creatingFileType;         /// @brief The file type user trying to create.
        std::filesystem::path selectedFile = ""; /// @brief Holds selected file for actions such as delete / rename that needs confirm.

        void RenderImGuiWindow();
        void RenderDirectoryItem(std::filesystem::directory_entry directoryEntry, int &itemSize);
        void HandleItemSelected(bool isDir, std::filesystem::path path);
        void HandleItemDoubleClicked(bool isDir, std::filesystem::path path);
        void RenderEditItem(int &itemSize);

    public:
        std::filesystem::path selectedItemPath;

        enum Events
        {
            OnItemSelect
        };

        inline std::string GetWindowName() override { return "Resource Browser"; }

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
    };
}