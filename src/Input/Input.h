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

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <Core/Window.h>
#include <Input/Key.h>

namespace DT
{
    namespace Input
    {
        inline glm::vec2 mousePosition;
        inline glm::vec2 mouseDelta;

        inline std::vector<int> keysDown;
        inline std::vector<int> keysUp;

        bool GetKey(int key);
        bool GetKeyPressed(int key);
        bool GetKeyReleased(int key);

        void Init();
        void Process();
        void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    }
}