#include <Panels/MenuBarPanel.h>

namespace DT
{
    void MenuBarPanel::Start(ContextPtr &ctx)
    {
        isOpen = true;

        if (!std::filesystem::exists(std::filesystem::current_path() / "imgui.ini"))
            SetDefaultLayout();
    }

    void MenuBarPanel::Update(ContextPtr &ctx)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Save"))
                    // engine.project.Save();
                    ;
                if (ImGui::MenuItem("Edit"))
                    Editor::GetPanel<ProjectPanel>()->isOpen = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem("Save"))
                    ctx.sceneManager->Save(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "Scenes" / "MainScene.json", *ctx.sceneManager->activeScene.data, ctx);

                if (ImGui::MenuItem("Load"))
                {
                    ctx.sceneManager->Load(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "Scenes" / "MainScene.json", *ctx.sceneManager->activeScene.data, ctx);
                    ctx.sceneManager->GetActiveScene().selectedEntity = entt::null;
                }

                if (ImGui::MenuItem("Create Entity"))
                    ctx.sceneManager->GetActiveScene().selectedEntity = ctx.sceneManager->GetActiveScene().CreateEntity();
                if (ImGui::MenuItem("Destroy Entity"))
                    ctx.sceneManager->GetActiveScene().DestroyEntity(ctx.sceneManager->GetActiveScene().selectedEntity);
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
                ImGui::TextUnformatted(ctx.debug->GetErr().c_str());
                ImGui::TextUnformatted(ctx.debug->GetLog().c_str());

                if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    Editor::GetPanel<ConsolePanel>()->isOpen = true;

                ImGui::EndMenuBar();
            }
            ImGui::End();
        }
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