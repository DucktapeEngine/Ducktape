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

#include <Core/Configuration.h>
#include <Renderer/Color.h>

namespace DT
{
    namespace Window
    {
        inline GLFWwindow *window;

        void Init();

        void Clear(Color color);
        void PollEvents();
        void Display();
        void Terminate();

        glm::vec2 GetSize();
        void SetSize(glm::vec2 size);

        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    };
}