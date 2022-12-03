/*
Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include "Editor.h"

namespace DT
{
    void Editor::Init(Engine &engine)
    {
        enginePtr = &engine;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(engine.window.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDragClickToInputText = true;

        io.Fonts->AddFontFromFileTTF((DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Fonts" / "Roboto" / "Roboto-Regular.ttf").string().c_str(), 15.f);
        SetDarkTheme();

        // Check if user have settings file
        const bool settingsExists = std::filesystem::exists(std::filesystem::current_path() / "imgui.ini");

        for (Panel *panel : panels)
            panel->Start(engine);

        MaximizeWindow();
    }

    void Editor::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /// @brief Renders dock layout for editor.
    /// Also creates default layout upon first run of Ducktape.
    void Editor::RenderDockLayout()
    {
        // Check if user have settings file
        static bool settingsExists = std::filesystem::exists(std::filesystem::current_path() / "imgui.ini");
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            dockspace_id = ImGui::DockSpaceOverViewport();

            // For setting up default layout
            if (!settingsExists)
            {
                settingsExists = true;
                // Menu panel is out of docking worries
                // also set menubar pointer for default layout requests
                menuBar = AddPanel<MenuBarPanel>();

                SetDefaultLayout();

                for (Panel *panel : panels)
                    panel->Start();
            }
        }
    }
    /// @brief Sets up default layout for editor.
    /// @param firstTime defines if its called from menu or first initialization
    void Editor::SetDefaultLayout(bool firstTime)
    {
        ImGuiID leftSplit;
        ImGuiID rightSplit;
        ImGuiID rightLeftSplit;

        // 0: Hierarchy
        // 1: Resource Browser
        // 2: Sceneview
        // 3: Console
        // 4: Inspector
        // Adding splits in spesific order because when a default layout is requested
        // (while running Ducktape) we have to keep panels alive.
        ImGuiID splits[5]{};

        // Clear out previously created nodes
        ImGui::DockBuilderRemoveNodeDockedWindows(dockspace_id, false);
        ImGui::DockBuilderRemoveNodeChildNodes(dockspace_id);

        // Split dockspace into two first as left and right
        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.25f, &leftSplit, &rightSplit);
        // Then split left split on top and bottom
        ImGui::DockBuilderSplitNode(leftSplit, ImGuiDir_Down, 0.4f, &splits[1], &splits[0]);
        // Now split right node (sceneview) to rightleft and rightright
        ImGui::DockBuilderSplitNode(rightSplit, ImGuiDir_Left, 0.65f, &rightLeftSplit, &splits[4]);
        // Finally split sceneview to have console on bottom of it
        ImGui::DockBuilderSplitNode(rightLeftSplit, ImGuiDir_Down, 0.25f, &splits[3], &splits[2]);
        // now dock our windows into the docking nodes we made above
        // DockBuilderDockWindow requires window name as first parameter, hence why panels have GetWindowName now.

        // If user already have a layout and requested default one again
        if (menuBar != nullptr && !firstTime)
        {
            for (int i = 1; i <= 5; i++)
            {
                ImGui::DockBuilderDockWindow(panels[i]->GetWindowName(), splits[i - 1]);
            }
        }
        // Theres no default layout or windows, set it up
        else
        {
            ImGui::DockBuilderDockWindow(AddPanel<HierarchyPanel>()->GetWindowName(), splits[0]);
            ImGui::DockBuilderDockWindow(AddPanel<ResourceBrowserPanel>()->GetWindowName(), splits[1]);
            ImGui::DockBuilderDockWindow(AddPanel<SceneViewPanel>()->GetWindowName(), splits[2]);
            ImGui::DockBuilderDockWindow(AddPanel<ConsolePanel>()->GetWindowName(), splits[3]);
            ImGui::DockBuilderDockWindow(AddPanel<InspectorPanel>()->GetWindowName(), splits[4]);
        }

        ImGui::DockBuilderFinish(dockspace_id);
    }

    void Editor::Render(Engine &engine)
    {
        // ImGui::DockSpaceOverViewport();
        RenderDockLayout();

        // Kind of event system when default layout is requested
        if (menuBar->RequestDefaultLayout)
        {
            menuBar->RequestDefaultLayout = false;
            SetDefaultLayout(false);
        }

        ImGui::fileDialog.Display();

        for (Panel *panel : panels)
            if (panel->isOpen)
                panel->Update(engine);
    }

    void Editor::EndFrame(Renderer &renderer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glBindFramebuffer(GL_FRAMEBUFFER, renderer.FBO);
    }

    void Editor::Terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        for (Panel *panel : panels)
            free(panel);
        panels.clear();
    }

    void Editor::Close()
    {
        glfwSetWindowShouldClose(enginePtr->window.window, true);
    }

    void Editor::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(enginePtr->window.window, title.c_str());
    }

    void Editor::SetIcon(std::filesystem::path path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLFWimage image;
            image.width = width;
            image.height = height;
            image.pixels = data;
            glfwSetWindowIcon(enginePtr->window.window, 1, &image);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load icon." << std::endl;
        }
    }

    glm::vec2 Editor::GetWindowPos()
    {
        int x, y;
        glfwGetWindowPos(enginePtr->window.window, &x, &y);
        return glm::vec2(x, y);
    }

    void Editor::SetWindowPos(const glm::vec2 &pos)
    {
        glfwSetWindowPos(enginePtr->window.window, pos.x, pos.y);
    }

    glm::vec2 Editor::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(enginePtr->window.window, &width, &height);
        return glm::vec2(width, height);
    }

    void Editor::SetWindowSizeLimits(const glm::vec2 &minSize, const glm::vec2 &maxSize)
    {
        glfwSetWindowSizeLimits(enginePtr->window.window, minSize.x, minSize.y, maxSize.x, maxSize.y);
    }

    void Editor::SetWindowAspectRatio(const int &numerator, const int &denominator)
    {
        glfwSetWindowAspectRatio(enginePtr->window.window, numerator, denominator);
    }

    void Editor::SetWindowSize(const glm::vec2 &size)
    {
        glfwSetWindowSize(enginePtr->window.window, size.x, size.y);
    }

    glm::vec2 Editor::GetWindowContentScale()
    {
        float x, y;
        glfwGetWindowContentScale(enginePtr->window.window, &x, &y);
        return glm::vec2(x, y);
    }

    float Editor::GetWindowOpacity()
    {
        return glfwGetWindowOpacity(enginePtr->window.window);
    }

    void Editor::SetWindowOpacity(const float &opacity)
    {
        glfwSetWindowOpacity(enginePtr->window.window, opacity);
    }

    void Editor::IconifyWindow()
    {
        glfwIconifyWindow(enginePtr->window.window);
    }

    void Editor::RestoreWindow()
    {
        glfwRestoreWindow(enginePtr->window.window);
    }

    void Editor::MaximizeWindow()
    {
        glfwMaximizeWindow(enginePtr->window.window);
    }

    void Editor::ShowWindow()
    {
        glfwShowWindow(enginePtr->window.window);
    }

    void Editor::HideWindow()
    {
        glfwHideWindow(enginePtr->window.window);
    }

    void Editor::FocusWindow()
    {
        glfwFocusWindow(enginePtr->window.window);
    }

    void Editor::RequestWindowAttention()
    {
        glfwRequestWindowAttention(enginePtr->window.window);
    }

    void Editor::SetVSync(const bool &vsync)
    {
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

#define rgb(r, g, b) ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.00f)

    void Editor::SetDarkTheme()
    {
        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
        style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style.GrabRounding = style.FrameRounding = 2.3f;
    }
}