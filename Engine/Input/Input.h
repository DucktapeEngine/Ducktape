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

#include <unordered_set>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <Core/Window.h>
#include <Input/Key.h>

namespace DT
{
    class Input
    {
    public:
        glm::vec2 mousePosition = glm::vec2(0.f);
        glm::vec2 mouseDelta = glm::vec2(0.f);

        std::unordered_set<int> keysDown;
        std::unordered_set<int> keysUp;
        std::unordered_set<int> mouseButtonsUp;
        std::unordered_set<int> mouseButtonsDown;

        GLFWwindow *window;

        bool GetKey(int key);
        bool GetKeyPressed(int key);
        bool GetKeyReleased(int key);

        bool GetMouseButton(int button);
        bool GetMouseButtonPressed(int button);
        bool GetMouseButtonReleased(int button);

        Input(GLFWwindow *window);
        void Process();
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    };
}