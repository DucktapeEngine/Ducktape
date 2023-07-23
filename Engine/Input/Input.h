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
#include <Core/Macro.h>

namespace DT
{
    class Engine;

    /**
     * @class Input
     * @brief Handles input events from the user.
     */
    class Input
    {
    public:
        glm::vec2 mousePosition = glm::vec2(0.f); /// The position of the mouse.
        glm::vec2 mouseDelta = glm::vec2(0.f);    /// The position change of the mouse.

        std::vector<std::function<void(Key, Action)>> onKeyEvents;      /// List of functions to be called on key events.
        std::vector<std::function<void(Button, Action)>> onMouseEvents; /// List of functions to be called on mouse events.

        GLFWwindow *window; /// Pointer to the OpenGL window.

        /**
         * @brief Constructs an Input object.
         * @param ctx A pointer to the context.
         */
        Input(ContextPtr &ctx);

        /**
         * @brief Checks if a key is currently held.
         * @param key The key to check.
         * @return True if the key is held, false otherwise.
         */
        bool IsKeyHeld(int key);

        /**
         * @brief Checks if a mouse button is currently held.
         * @param button The button to check.
         * @return True if the button is held, false otherwise.
         */
        bool IsMouseButtonHeld(int button);

        /**
         * @brief Sets the callback function for key events.
         * @param onKeyEvent The callback function to set.
         */
        void OnKeyEvent(std::function<void(Key, Action)> onKeyEvent);

        /**
         * @brief Sets the callback function for mouse events.
         * @param onMouseEvent The callback function to set.
         */
        void OnMouseEvent(std::function<void(Button, Action)> onMouseEvent);

        /**
         * @brief Processes input events.
         */
        void Process();

        /**
         * @brief Callback function for key events.
         * @param window The window that received the event.
         * @param key The keyboard key that was pressed or released.
         * @param scancode The system-specific scancode of the key.
         * @param action GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
         * @param mods Bit field describing which modifier keys were held down.
         */
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        /**
         * @brief Callback function for mouse button events.
         * @param window The window that received the event.
         * @param button The mouse button that was pressed or released.
         * @param action GLFW_PRESS or GLFW_RELEASE.
         * @param mods Bit field describing which modifier keys were held down.
         */
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    };
}
