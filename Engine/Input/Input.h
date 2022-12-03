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
#include <functional>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Input/Key.h>
#include <Core/Context.h>

namespace DT
{
    class Engine;

    class Input
    {
    public:
        glm::vec2 mousePosition = glm::vec2(0.f); ///< @brief The position of the mouse.
        glm::vec2 mouseDelta = glm::vec2(0.f);    ///< @brief The position change of the mouse.

        std::vector<std::function<void(Key, Action)>> onKeyEvents;
        std::vector<std::function<void(Button, Action)>> onMouseEvents;

        GLFWwindow *window; ///< @brief Pointer to the OpenGL window.

        Input(GLFWwindow *window);

        bool IsKeyHeld(int key);
        bool IsMouseButtonHeld(int button);

        void OnKeyEvent(std::function<void(Key, Action)> onKeyEvent);
        void OnMouseEvent(std::function<void(Button, Action)> onMouseEvent);

        void Process();
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    };
}
