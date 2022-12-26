#include <Panels/MenuBarPanel.h>

namespace DT
{
    void MenuBarPanel::Start(Engine &engine)
    {
        isOpen = true;

        if (!std::filesystem::exists(std::filesystem::current_path() / "imgui.ini"))
            SetDefaultLayout();
    }

    void MenuBarPanel::Update(Engine &engine)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Save"))
                    engine.project.Save();
                if (ImGui::MenuItem("Edit"))
                    Editor::GetPanel<ProjectPanel>()->isOpen = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem("Create Entity"))
                    engine.activeScene->CreateEntity();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Panels"))
            {
                if (ImGui::MenuItem("Console"))
                    Editor::GetPanel<ConsolePanel>()->isOpen = true;
                if (ImGui::MenuItem("Scene"))
                    Editor::GetPanel<ScenePanel>()->isOpen = true;
                if (ImGui::MenuItem("Properties"))
                    Editor::GetPanel<PropertiesPanel>()->isOpen = true;
                if (ImGui::MenuItem("Resource Browser"))
                    Editor::GetPanel<ResourceBrowserPanel>()->isOpen = true;
                if (ImGui::MenuItem("Scene View"))
                    Editor::GetPanel<SceneViewPanel>()->isOpen = true;
                if (ImGui::MenuItem("Resource Inspector"))
                    Editor::GetPanel<ResourceInspectorPanel>()->isOpen = true;
                if (ImGui::MenuItem("Project Browser"))
                    Editor::GetPanel<DucktapeEditorPanel>()->isOpen = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Editor"))
            {
                if (ImGui::MenuItem("Load Default layout"))
                {
                    SetDefaultLayout();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGuiViewportP *viewport = (ImGuiViewportP *)(void *)ImGui::GetMainViewport();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

        ImGuiStyle &style = ImGui::GetStyle();

        if (ImGui::BeginViewportSideBar("##MainBar", viewport, ImGuiDir_Down, ImGui::GetFrameHeight(), window_flags))
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted(engine.debug.GetErr().c_str());
                ImGui::TextUnformatted(engine.debug.GetLog().c_str());

                if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    Editor::GetPanel<ConsolePanel>()->isOpen = true;

                ImGui::EndMenuBar();
            }
            ImGui::End();
        }

        /*
        Use this for the play/pause/stop features in the Game window.

        const float iconSize = 25.f;

        if (ImGui::ImageButton((ImTextureID)(uintptr_t)playIconId, ImVec2(iconSize, iconSize)))
            engine.debug << "Game Runtime not yet supported." << std::endl;
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)pauseIconId, ImVec2(iconSize, iconSize)))
            engine.debug << "Game Runtime not yet supported." << std::endl;
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)stopIconId, ImVec2(iconSize, iconSize)))
            engine.debug << "Game Runtime not yet supported." << std::endl;

        playIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "start.png"))->id;
        pauseIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "pause.png"))->id;
        stopIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "stop.png"))->id;
        */
    }

    void MenuBarPanel::SetDefaultLayout()
    {
        Editor::GetPanel<ConsolePanel>()->isOpen = true;
        Editor::GetPanel<ScenePanel>()->isOpen = true;
        Editor::GetPanel<PropertiesPanel>()->isOpen = true;
        Editor::GetPanel<ResourceBrowserPanel>()->isOpen = true;
        Editor::GetPanel<SceneViewPanel>()->isOpen = true;
        Editor::GetPanel<ResourceInspectorPanel>()->isOpen = true;

        ImGuiIO &io = ImGui::GetIO();
        if (!(io.ConfigFlags & ImGuiConfigFlags_DockingEnable))
            return;

        ImGui::DockBuilderRemoveNodeDockedWindows(Editor::dockspaceId, false);
        ImGui::DockBuilderRemoveNodeChildNodes(Editor::dockspaceId);

        // Scene
        ImGuiID scene;
        ImGuiID sceneViewPropertiesResourceInspector;
        ImGui::DockBuilderSplitNode(Editor::dockspaceId, ImGuiDir_Left, 0.15f, &scene, &sceneViewPropertiesResourceInspector);
        ImGui::DockBuilderDockWindow("Scene", scene);

        // Scene View
        ImGuiID sceneView;
        ImGuiID sceneViewConsoleResourceBrowser;
        ImGuiID propertiesResourceInspector;
        ImGui::DockBuilderSplitNode(sceneViewPropertiesResourceInspector, ImGuiDir_Left, 0.8f, &sceneViewConsoleResourceBrowser, &propertiesResourceInspector);

        ImGuiID consoleResourceBrowser;
        ImGui::DockBuilderSplitNode(sceneViewConsoleResourceBrowser, ImGuiDir_Up, 0.7f, &sceneView, &consoleResourceBrowser);
        ImGui::DockBuilderDockWindow(Editor::GetPanel<SceneViewPanel>()->GetWindowName().c_str(), sceneView);

        // Properties & Resource Inspector
        ImGui::DockBuilderDockWindow("Properties", propertiesResourceInspector);
        ImGui::DockBuilderDockWindow("Resource Inspector", propertiesResourceInspector);

        // Console & Resource Browser
        ImGui::DockBuilderDockWindow("Console", consoleResourceBrowser);
        ImGui::DockBuilderDockWindow("Resource Browser", consoleResourceBrowser);

        // Build
        ImGui::DockBuilderFinish(Editor::dockspaceId);
    }
}