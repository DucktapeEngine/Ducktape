#include <Panels/ResourceBrowserPanel.h>

namespace DT
{
    /// @brief Handles main imgui render for resource browser window.
    void ResourceBrowserPanel::RenderImGuiWindow()
    {
        isOpen = true;
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        filter.Draw("Filter");
        ImGui::Separator();

        // Make a scrollable region in case it doesn't fit
        ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar;
        static float navbarHeight = 20.0f;
        float totalNavbarSize = 0.0f;
        ImGui::BeginChild("Navbar##ResourceBrowser", {-1, navbarHeight}, false, child_flags);
        // Make resource button match ducktape color (and transparent button)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.980f, 0.871f, 0.0490f, 1.00f));
        if (currentDir == rootDir)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.67f, 0.67f, 0.67f, 0.39f));
        else
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        std::string rootDirName = rootDir.filename().string();
        if (ImGui::Button(rootDirName.c_str()))
            currentDir = rootDir;
        totalNavbarSize += ImGui::GetItemRectSize().x;
        ImGui::PopStyleColor(2);

        // Get relative path between root and current
        std::filesystem::path relativePath = std::filesystem::relative(currentDir, rootDir);
        std::filesystem::path tempDir = rootDir;
        std::filesystem::path::iterator it = relativePath.begin();

        // Traverse until reach currentDir to add navigating buttons
        while (tempDir != currentDir)
        {
            ImGui::SameLine();
            ImGui::TextUnformatted(">");
            totalNavbarSize += ImGui::GetItemRectSize().x + 8.0f;
            ImGui::SameLine();
            tempDir /= *it;
            // Transparent button style (active directory will be highlighted)
            if (tempDir == currentDir)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.67f, 0.67f, 0.67f, 0.39f));
            else
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            std::string filename = tempDir.filename().string();
            ImGui::PushID(filename.c_str());
            ImGui::Button(filename.c_str());
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                currentDir = tempDir;
            }
            if (tempDir == currentDir)
                ImGui::SetScrollHereX();
            ImGui::PopID();
            totalNavbarSize += ImGui::GetItemRectSize().x + 8.0f;
            ImGui::PopStyleColor();
            ++it;
        }
        ImGui::EndChild();
        // Trying to implement adding height to navbar when scrolling is visible
        ImVec2 avail = ImGui::GetContentRegionAvail();
        if (totalNavbarSize > avail.x)
            navbarHeight = 40.0f;
        else
            navbarHeight = 20.0f;
        static int itemSize = 24;

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));

        // TODO: Listbox context menu does not pop up (Doesn't listboxes support context menus??)
        if (ImGui::BeginListBox("##filesListBox", ImVec2(-FLT_MIN, avail.y - 28)))
        {
            // HACK: Seems like this is best one that works so far for a context menu for listboxes.
            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup("Test");
            }
            if (ImGui::BeginPopup("Test"))
            {
                if (ImGui::BeginMenu("Create..."))
                {
                    if (ImGui::MenuItem("Folder"))
                    {
                        fileAction = FileAction_Create;
                        creatingFileType = FileCreateType_Folder;
                    }
                    if (ImGui::MenuItem("File"))
                    {
                        fileAction = FileAction_Create;
                        creatingFileType = FileCreateType_File;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }
            // Try to list all files when filtering
            float totalSizeOnColumn = 0;
            if (filter.IsActive())
            {
                for (std::filesystem::directory_entry directoryEntry : std::filesystem::recursive_directory_iterator(rootDir))
                {
                    std::filesystem::path path = directoryEntry.path();
                    std::string filename = path.filename().string();
                    if (filter.PassFilter(filename.c_str()))
                    {
                        RenderDirectoryItem(directoryEntry, itemSize);
                        totalSizeOnColumn += ImGui::GetItemRectSize().x + itemSize;

                        // Custom wrap for items for column-like layout
                        if (itemSize >= columnSwitchSize && totalSizeOnColumn < avail.x)
                            ImGui::SameLine();
                        else if (totalSizeOnColumn > avail.x)
                            totalSizeOnColumn = 0;
                    }
                }
            }
            // List only active dir
            else
            {
                for (std::filesystem::directory_entry directoryEntry : std::filesystem::directory_iterator(currentDir))
                {
                    RenderDirectoryItem(directoryEntry, itemSize);
                    totalSizeOnColumn += ImGui::GetItemRectSize().x + itemSize;
                    // Custom wrap for items for column-like layout
                    if (itemSize >= columnSwitchSize && totalSizeOnColumn < avail.x)
                        ImGui::SameLine();
                    else if (totalSizeOnColumn > avail.x)
                        totalSizeOnColumn = 0;
                }
            }
            if (fileAction == FileAction_Create)
            {
                RenderEditItem(itemSize);
            }
            else if (fileAction == FileAction_Delete)
            {
                fileAction = FileAction_None;
                ImGui::OpenPopup("Delete");
            }

            if (ImGui::BeginPopupModal("Delete"))
            {
                std::string prompt = std::string("Are you sure you want to delete \"") + selectedFile.filename().string() + (!selectedFile.has_extension() ? "\" and its contents?" : "\"?");
                ImGui::TextUnformatted(prompt.c_str());
                ImGui::Separator();
                if (ImGui::Button("No", {36, 24}))
                {
                    selectedFile = "";
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0.77f, 0.2f, 0.2f, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_Button, {0.0f, 0.0f, 0.0f, 0.0f});
                if (ImGui::Button("Yes", {36, 24}))
                {
                    if (!std::filesystem::remove_all(selectedFile))
                    {
                        std::cout << "Couldn't delete file: " << selectedFile.filename().string() << std::endl;
                    }
                    selectedFile = "";
                    ImGui::CloseCurrentPopup();
                }
                ImGui::PopStyleColor(2);
                ImGui::EndPopup();
            }
            ImGui::EndListBox();
        }
        ImGui::PopStyleColor();
        /* if (ImGui::BeginPopupModal("ModalNewFile"), NULL)
         {
             ImGui::InputText("File name", &newFileName);
             ImGui::EndPopup();
         }*/
        ImGui::Separator();
        ImGui::SliderInt("Item Size", &itemSize, 16, 48);

        ImGui::End();
    }
    /// @brief Renders each item for resource browser.
    /// @param directoryEntry entry on file path
    /// @param itemSize item's size for resource browser (controlled by slider)
    void ResourceBrowserPanel::RenderDirectoryItem(std::filesystem::directory_entry directoryEntry, int &itemSize)
    {
        std::filesystem::path path = directoryEntry.path();
        std::string filename = path.filename().string();

        // Render editable label instead when renaming this file
        if (fileAction == FileAction_Rename && path == selectedFile)
        {
            RenderEditItem(itemSize);
            return;
        }

        const bool isDir = directoryEntry.is_directory();
        const bool onColumnLayout = itemSize >= columnSwitchSize;
        ImVec2 avail = ImGui::GetContentRegionAvail();

        unsigned int iconId = isDir ? folderIconId : ResourceInterface::GetIcon(path.extension().string());

        ImGui::PushID(filename.c_str());

        bool selected = selectedItemPath == path;

        if (!selected)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButtonWithText((ImTextureID)(uintptr_t)iconId, filename.c_str(), {static_cast<float>(itemSize), static_cast<float>(itemSize)}, onColumnLayout, {0, 1}, {1, 0});

        // Since same functionality used twice, grouped them onto same function, you'll see below its used again
        // HACK: ^ Image and text are one group now thanks to new implementation, but it will still use same method.

        HandleItemSelected(isDir, path);
        HandleItemDoubleClicked(isDir, path);

        // TODO: Add more context menu options for item
        if (ImGui::BeginPopupContextItem())
        {
            /*if(ImGui::Selectable("Copy"))
            {
                copiedFile = path;
            }*/

            if (!isDir && ImGui::MenuItem("Reimport"))
            {
                ResourceImporter::Reimport(directoryEntry.path());
            }

            if (ImGui::BeginMenu("Create..."))
            {
                if (ImGui::MenuItem("Folder"))
                {
                    fileAction = FileAction_Create;
                    creatingFileType = FileCreateType_Folder;
                }
                if (ImGui::MenuItem("File"))
                {
                    fileAction = FileAction_Create;
                    creatingFileType = FileCreateType_File;
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Show In Explorer"))
            {
#ifdef _WIN32
                Platform::Execute(currentDir.string());
#endif
#ifdef __linux__
                Platform::Execute("xdg-open " + path.string());
#endif
            }
            if (ImGui::MenuItem("Rename"))
            {
                fileAction = FileAction_Rename;
                selectedFile = path;
            }
            if (ImGui::MenuItem("Delete"))
            {
                fileAction = FileAction_Delete;
                selectedFile = path;
            }
            ImGui::EndPopup();
        }
        if (!selected)
            ImGui::PopStyleColor();
        ImGui::PopID();
    }

    /// @brief Renders edit action based items (create, rename, ...) for resource browser.
    /// @param itemSize Current item size on resource browser.
    void ResourceBrowserPanel::RenderEditItem(int &itemSize)
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            fileAction = FileAction_None;
            selectedFile = "";
            return;
        }

        unsigned int iconId = creatingFileType == FileCreateType_Folder ? folderIconId : fileIconId;

        if (fileAction == FileAction_Rename)
            iconId = selectedFile.has_extension() ? ResourceInterface::GetIcon(selectedFile.extension().string()) : folderIconId;

        /*ImGui::Image((ImTextureID)(uintptr_t)iconId, { itemSize,itemSize }, { 0, 1 }, { 1, 0 });
        if (itemSize < columnSwitchSize)
            ImGui::SameLine();*/

        if (fileAction == FileAction_Rename && selectedFile == "")
            return;
        static char buf[128];

        if (fileAction != FileAction_Rename && creatingFileType == FileCreateType_File)
            strcpy(buf, "New File");
        else if (fileAction != FileAction_Rename && creatingFileType == FileCreateType_Folder)
            strcpy(buf, "New Folder");
        else
            strcpy(buf, selectedFile.stem().string().c_str());

        // ImGui::Image((ImTextureID)(uintptr_t)iconId, { itemSize,itemSize }, { 0, 1 }, { 1, 0 });
        // ImGui::SameLine();

        // ImGui::SetKeyboardFocusHere(0);
        // ImGui::InputText("##inputNewFile", buf, IM_ARRAYSIZE(buf));

        bool onColumnLayout = itemSize >= columnSwitchSize;

        ImGui::ImageWithInputText((ImTextureID)(uintptr_t)iconId, "##inputNewFile", buf, IM_ARRAYSIZE(buf), {itemSize, itemSize}, {0, 1}, {1, 0}, onColumnLayout);
        ImGui::SetKeyboardFocusHere(-1);
        if (ImGui::IsItemDeactivatedAfterEdit() || ImGui::IsKeyPressed(ImGuiKey_Enter))
        {
            if (fileAction == FileAction_Rename)
            {
                std::string ext = selectedFile.extension().string();
                try
                {
                    std::filesystem::path p = currentDir / (std::string(buf) + ext);
                    std::filesystem::rename(selectedFile, p);
                    fileAction = FileAction_None;
                    selectedFile = "";
                }
                catch (...)
                {
                    std::cout << "[Error] Failed to rename file: " << selectedFile.stem().string() << " to " << buf << std::endl;
                }
            }
            else if (creatingFileType == FileCreateType_File)
            {
                std::ofstream file((currentDir / buf).string());
                if (!file)
                {
                    std::cout << "[Error] Can't create requested file: " << buf << std::endl;
                }
                else
                    fileAction = FileAction_None;
                file.close();
            }
            else
            {
                if (std::filesystem::create_directory(currentDir / buf))
                {
                    fileAction = FileAction_None;
                }
                else
                {
                    std::cout << "[Error] Failed to create folder: " << buf << std::endl;
                }
            }
        }
    }

    void ResourceBrowserPanel::HandleItemDoubleClicked(bool isDir, std::filesystem::path path)
    {
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if (isDir)
            {
                currentDir = rootDir / std::filesystem::relative(path, rootDir);
                filter.Clear();
            }
            else
            {
#ifdef _WIN32
                Platform::Execute(path.string());
#endif
#ifdef __linux__
                Platform::Execute("xdg-open " + path.string());
#endif
            }
        }
    }

    void ResourceBrowserPanel::HandleItemSelected(bool isDir, std::filesystem::path path)
    {
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            selectedItemPath = path;

            if (!isDir)
                Invoke(Events::OnItemSelect);
        }
    }

    /// @brief Called when this panel is added and ready to start.
    void ResourceBrowserPanel::Start(Engine &engine)
    {
        rootDir = DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox";
        resourceDir = DUCKTAPE_ROOT_DIR / "Resources" / "Editor";
        currentDir = rootDir;
        // Note that icons are from https://www.icons8.com and not fully copyright free.
        // TODO: Add self drawn icons

        folderIconId = Texture::LoadResource(ResourceManager::GetRID(resourceDir / "Icons" / "ResourceBrowser" / "folder.png"))->id;
        fileIconId = Texture::LoadResource(ResourceManager::GetRID(resourceDir / "Icons" / "ResourceBrowser" / "file.png"))->id;
    }

    /// @brief Called when this panel is updated each frame.
    void ResourceBrowserPanel::Update(Engine &engine)
    {
        RenderImGuiWindow();
    }
}