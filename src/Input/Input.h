/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <Input/Key.h>
#include <Input/MouseMode.h>
#include <Core/Window.h>

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