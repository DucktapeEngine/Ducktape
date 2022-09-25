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

#include <vector>
#include <stdexcept>
#include <iostream>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/stb_image.h>

#include <Core/Configuration.h>

namespace DT
{
    class Window
    {
    public:
        GLFWwindow *window = nullptr;

        Window(const Configuration &config);

        void Clear(glm::vec4 color);
        void PollEvents();
        void SwapBuffers();
        ~Window();

        void Close();
        void SetTitle(const std::string &title);
        void SetIcon(const std::string &path);
        glm::vec2 GetWindowPos();
        void SetWindowPos(const glm::vec2 &pos);
        glm::vec2 GetWindowSize();
        void SetWindowSizeLimits(const glm::vec2 &minSize, const glm::vec2 &maxSize);
        void SetWindowAspectRatio(const int &numerator, const int &denominator);
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

        static void ErrorCallback(int code, const char *description);
        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
        static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
    };
}