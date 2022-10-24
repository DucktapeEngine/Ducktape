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

#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Renderer/Renderer.h>
#include <Core/Window.h>
#include <Core/Engine.h>
#include <Panels/Panel.h>

namespace DT
{
    namespace Editor
    {
        inline bool showDemoWindow = true;
        inline Engine *enginePtr;

        void Init(Engine &engine);
        void NewFrame();
        void Render(Engine &engine);
        void EndFrame(Renderer &renderer);
        void Terminate();

        void Close();
        void SetTitle(const std::string &title);
        void SetIcon(std::filesystem::path path);
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
        void SetDarkTheme();
        inline std::vector<Panel*> panels;

        template<typename T>
        T* AddPanel()
        {
            T* Tptr = new T();
            panels.push_back(Tptr);
            return Tptr;
        }
    }
}