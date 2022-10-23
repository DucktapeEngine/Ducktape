#include "ResourceBrowserPanel.h"

namespace DT
{
    void ResourceBrowserPanel::RenderImGuiWindow()
    {
        ImGui::Begin("Resource Browser");
        Filter.Draw("Filter");
        ImGui::Separator();
        // Make resource button match ducktape color (and transparent button)
        ImGui::PushStyleColor(ImGuiCol_Text,ImVec4(0.980f, 0.871f, 0.0490f,1.00f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        if (ImGui::Button("Resources"))
            currentDir = rootDir;
        ImGui::PopStyleColor(2);

        // Get relative path between root and current
        std::filesystem::path relativePath = std::filesystem::relative(currentDir,rootDir);
        std::filesystem::path tempDir = rootDir;
        std::filesystem::path::iterator it = relativePath.begin();
        // Traverse until reach currentDir to add navigating buttons
        while(tempDir!=currentDir)
        {
            ImGui::SameLine();
            ImGui::TextUnformatted(">");
            ImGui::SameLine();
            tempDir /= *it;
            // Transparent button style
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            if(ImGui::Button(tempDir.filename().string().c_str()))
                currentDir = tempDir;
            ImGui::PopStyleColor();
            ++it;
        }
        
        static int itemSize=16;
        static int selectedIndex=0;
        int i=0;
        
        ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0,0,0,0));
        ImVec2 avail = ImGui::GetContentRegionAvail();
        if(ImGui::BeginListBox("##filesListBox",ImVec2(-FLT_MIN,avail.y - 28)))
        {
            /*if(itemSize>24.0f)
            {
                int cellSize = itemSize*2;
                int columnCount = (int)(avail.x/cellSize);
                if(columnCount<1)
                    columnCount=1;
                ImGui::Columns(columnCount,0,false);
            }*/
            // Try to list all files when filtering
            float totalSizeOnColumn=0;
            if(Filter.IsActive())
            {
                for (std::filesystem::directory_entry directoryEntry : std::filesystem::recursive_directory_iterator(rootDir))
                {
                    std::filesystem::path path = directoryEntry.path();
                    const char* filename = path.filename().string().c_str();
                    if(Filter.PassFilter(filename))
                    {
                        RenderDirectoryItem(directoryEntry,itemSize);
                        totalSizeOnColumn+=ImGui::GetItemRectSize().x + itemSize;
                        // Custom wrap for items for column-like layout
                        if(itemSize>=columnSwitchSize && totalSizeOnColumn<avail.x)
                        {
                            ImGui::SameLine();
                        } 
                        else if(totalSizeOnColumn>avail.x) totalSizeOnColumn=0;
                        i++;
                    }
                }
            }
            // List only active dir
            else
            {
                for (std::filesystem::directory_entry directoryEntry : std::filesystem::directory_iterator(currentDir))
                {
                    RenderDirectoryItem(directoryEntry,itemSize);   
                    totalSizeOnColumn+=ImGui::GetItemRectSize().x + itemSize;
                    // Custom wrap for items for column-like layout
                    if(itemSize>=columnSwitchSize && totalSizeOnColumn<avail.x) ImGui::SameLine();
                    else if(totalSizeOnColumn>avail.x) totalSizeOnColumn=0;
                    i++;
                }
            }
            ImGui::EndListBox();
        }
        ImGui::PopStyleColor();
        ImGui::Separator();
        ImGui::SliderInt("Item Size", &itemSize, 16, 48);    
        ImGui::End();
    }
    /// @brief Draws each item for resource browser using ImGui.
    /// @param directoryEntry entry on file path
    /// @param itemSize item's size for resource browser (controlled by slider)
    /// @param i current iteration
    /// @param selectedIndex selected item index
    void ResourceBrowserPanel::RenderDirectoryItem(std::filesystem::directory_entry directoryEntry,int& itemSize)
    {
        std::filesystem::path path = directoryEntry.path();
        std::string filename = path.filename().string();

        const bool isDir = directoryEntry.is_directory();
        const bool onColumnLayout = itemSize>=columnSwitchSize;
        ImVec2 avail = ImGui::GetContentRegionAvail();
        // Get id for file type textures (this will be enhanced to identify different file types on future)
        GLuint iconID = isDir?folderIconID:GetKnownIconID(path);
        ImGui::PushID(filename.c_str());
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButtonWithText((ImTextureID)(uintptr_t)iconID,filename.c_str(),{ static_cast<float>(itemSize), static_cast<float>(itemSize) },onColumnLayout, { 0, 1 }, { 1, 0 });
        // Since same functionality used twice, grouped them onto same function, you'll see below its used again
        // HACK: ^ Image and text are one group now thanks to new implementation, but it will still use same method.
        OnItemDoubleClicked(isDir,path);

        // TODO: Add more context menu options for item
        if(ImGui::BeginPopupContextItem())
        {
            /*if(ImGui::Selectable("Copy"))
            {
                copiedFile = path;
            }*/

            if(ImGui::MenuItem("Show In Explorer"))
            {   
#ifdef _WIN32
                ShellExecute(NULL, NULL, currentDir.string().c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif
#ifdef __linux__
                // this gets default file manager
                // xdg-mime query default inode/directory
                // but gonna try xdg-open first
                std::string command = "xdg-open " + path.string();
                system(command.c_str());
#endif
            }   
            ImGui::EndPopup();
        }

        ImGui::PopStyleColor();
        ImGui::PopID();
    }

    /// @brief Checks if item is double clicked on resource browser.
    /// @param isDir pass this as if item is directory
    /// @param path item's path
    void ResourceBrowserPanel::OnItemDoubleClicked(bool isDir,std::filesystem::path path)
    {
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if(isDir)
            {
                currentDir = rootDir / std::filesystem::relative(path,rootDir); 
                Filter.Clear();
            }
            else 
            {
#ifdef _WIN32
                ShellExecute(NULL, NULL, path.string().c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif
#ifdef __linux__
                // this gets default file manager
                // xdg-mime query default inode/directory
                // but gonna try xdg-open first
                std::string command = "xdg-open " + path.string();
                system(command.c_str());
#endif
            }
        }
    }

    unsigned int ResourceBrowserPanel::GetKnownIconID(std::filesystem::path path)
    {
        std::string ext = path.extension().string().substr(1);
        std::string iconPath = rootDir.string()+"/Icons/"+ext+".png";
        if (ext == "jpg" || ext == "png" || ext == "jpeg")
                return Texture(rootDir.string()+"/Icons/image.png","diffuse").id;
        if (std::filesystem::exists(iconPath))
            return Texture(iconPath,"diffuse").id;
        else return Texture(rootDir.string()+"/Icons/file.png","diffuse").id;
    }

    void ResourceBrowserPanel::Start()
    {
        rootDir=std::filesystem::current_path().parent_path() / "Resources";
        currentDir = rootDir; 
        // Note that icons are from https://www.icons8.com and not fully copyright free.
        // TODO: Add self drawn icons
        folderIconID = Texture((rootDir / "Icons" / "folder.png").string(),"diffuse").id;
        fileIconID = Texture((rootDir / "Icons" / "file.png").string(),"diffuse").id;
    }
    void ResourceBrowserPanel::Update(Engine &engine)
    {
        RenderImGuiWindow();
    }
    void ResourceBrowserPanel::Destroy(){}
}