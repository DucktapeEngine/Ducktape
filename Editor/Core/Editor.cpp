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
}