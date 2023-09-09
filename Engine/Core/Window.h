/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
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

#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Serialization.h>
#include <Core/ContextPtr.h>

namespace DT
{
    class Input;

    class Window
    {
    protected:
        bool hideWindow = false;                         /// Flag indicating whether the window is hidden.
        glm::vec2 windowSize = glm::vec2(500.f, 500.f);  /// The size of the window.
        std::string windowTitle = "Ducktape Editor"; /// The title of the window.
        bool drawWireframe = false;                      /// Flag indicating whether to draw in wireframe mode.
        std::filesystem::path windowIconPath;            /// The path to the window icon.
        bool vsync = true;                               /// Flag indicating whether VSync is enabled.
    
    public:
        GLFWwindow *window = nullptr; /// The GLFW window handle.

        Window(const json &data, ContextPtr &ctx);
        ~Window();

        void Clear(glm::vec4 color);
        void PollEvents();
        void SwapBuffers();

        void Close();
        void SetTitle(const std::string &title);
        void SetIcon(std::filesystem::path path);
        glm::vec2 GetWindowPos();
        void SetWindowPos(const glm::vec2 &pos);
        glm::vec2 GetWindowSize();
        void SetWindowSize(const glm::vec2 &size);
        glm::vec2 GetWindowContentScale();
        float GetWindowOpacity();
        void SetWindowOpacity(const float &opacity);
        void IconifyWindow();
        void RestoreWindow();
        void MaximizeWindow();
        void ShowWindow();
        void HideWindow();
        void FocusWindow();
        void RequestWindowAttention();
        void SetVSync(const bool &vsync);
        bool GetMinimized();

        static void ErrorCallback(int code, const char *description);
        static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);

        IN_SERIALIZE(Window, hideWindow, windowSize, windowTitle, drawWireframe, windowIconPath, vsync);
    };
}