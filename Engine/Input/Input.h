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
#include <GLFW/glfw3.h>

#include <Input/Key.h>
#include <Core/UserPointer.h>

namespace DT
{
    class Engine;
    
    class Input
    {
    public:
        glm::vec2 mousePosition = glm::vec2(0.f);       ///< @brief The position of the mouse.
        glm::vec2 mouseDelta = glm::vec2(0.f);          ///< @brief The position change of the mouse.

        std::unordered_set<int> keysDown;               ///< @brief The keys that are being pressed.
        std::unordered_set<int> keysUp;                 ///< @brief The keys that are released.
        std::unordered_set<int> mouseButtonsUp;         ///< @brief The mouse buttons that are being pressed.
        std::unordered_set<int> mouseButtonsDown;       ///< @brief The mouse buttons that are released.

        GLFWwindow *window;                             ///< @brief Pointer to the OpenGL window.

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
