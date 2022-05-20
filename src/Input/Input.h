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

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <Input/Key.h>
#include <Input/MouseMode.h>
#include <Core/Window.h>
#include <Core/Macro.h>

namespace Ducktape
{
    class Input
    {
    public:
        Window *activeWindow;

        std::unordered_map<Key, bool> keyHeldMap;
        std::unordered_map<Key, bool> keyPressedMap;
        std::unordered_map<Key, bool> keyReleasedMap;

        std::unordered_map<int, bool> mouseHeldMap;
        std::unordered_map<int, bool> mousePressedMap;
        std::unordered_map<int, bool> mouseReleasedMap;

        glm::vec2 mousePosition;
        glm::vec2 scrollDelta;

        void Init(Window &window);
        void Tick(Window &window);
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        bool KeyHeld(Key key);
        bool KeyPressed(Key key);
        bool KeyReleased(Key key);
        void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        void SetMouseMode(MouseMode mode, Window &window);
        bool MouseHeld(int button);
        bool MousePressed(int button);
        bool MouseReleased(int button);
        void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
        bool JoystickConnected(int joystick);
        std::vector<float> JoystickAxes(int joystick);
        std::vector<unsigned char> JoystickButtons(int joystick);
        std::string GetClipboard(Window &window);
        void SetClipboard(std::string string, Window &window);
    };
}