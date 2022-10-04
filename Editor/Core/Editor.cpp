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

#include <Core/Editor.h>

namespace DT
{
    void Editor::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
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
    }

    void Editor::Close()
    {
        glfwSetWindowShouldClose(engine->window.window, true);
    }

    void Editor::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(engine->window.window, title.c_str());
    }

    void Editor::SetIcon(const std::string &path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLFWimage image;
            image.width = width;
            image.height = height;
            image.pixels = data;
            glfwSetWindowIcon(engine->window.window, 1, &image);
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
        glfwGetWindowPos(engine->window.window, &x, &y);
        return glm::vec2(x, y);
    }

    void Editor::SetWindowPos(const glm::vec2 &pos)
    {
        glfwSetWindowPos(engine->window.window, pos.x, pos.y);
    }

    glm::vec2 Editor::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(engine->window.window, &width, &height);
        return glm::vec2(width, height);
    }

    void Editor::SetWindowSizeLimits(const glm::vec2 &minSize, const glm::vec2 &maxSize)
    {
        glfwSetWindowSizeLimits(engine->window.window, minSize.x, minSize.y, maxSize.x, maxSize.y);
    }

    void Editor::SetWindowAspectRatio(const int &numerator, const int &denominator)
    {
        glfwSetWindowAspectRatio(engine->window.window, numerator, denominator);
    }

    void Editor::SetWindowSize(const glm::vec2 &size)
    {
        glfwSetWindowSize(engine->window.window, size.x, size.y);
    }

    glm::vec2 Editor::GetWindowContentScale()
    {
        float x, y;
        glfwGetWindowContentScale(engine->window.window, &x, &y);
        return glm::vec2(x, y);
    }

    float Editor::GetWindowOpacity()
    {
        return glfwGetWindowOpacity(engine->window.window);
    }

    void Editor::SetWindowOpacity(const float &opacity)
    {
        glfwSetWindowOpacity(engine->window.window, opacity);
    }

    void Editor::IconifyWindow()
    {
        glfwIconifyWindow(engine->window.window);
    }

    void Editor::RestoreWindow()
    {
        glfwRestoreWindow(engine->window.window);
    }

    void Editor::MaximizeWindow()
    {
        glfwMaximizeWindow(engine->window.window);
    }

    void Editor::ShowWindow()
    {
        glfwShowWindow(engine->window.window);
    }

    void Editor::HideWindow()
    {
        glfwHideWindow(engine->window.window);
    }

    void Editor::FocusWindow()
    {
        glfwFocusWindow(engine->window.window);
    }

    void Editor::RequestWindowAttention()
    {
        glfwRequestWindowAttention(engine->window.window);
    }

    void Editor::SetVSync(const bool &vsync)
    {
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }
}