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

#include <Input/Input.h>

namespace Ducktape
{
    void Input::Init(Window &window)
    {
        glfwSetWindowUserPointer(window.window, reinterpret_cast<void *>(this));
        glfwSetKeyCallback(window.window, KeyCallback);
    }

    void Input::Tick(Window &window)
    {
        keyPressedMap.clear();
        keyReleasedMap.clear();

        mousePressedMap.clear();
        mouseReleasedMap.clear();

        double xpos, ypos;
        glfwGetCursorPos(window.window, &xpos, &ypos);
        mousePosition = glm::vec2(xpos, ypos);
    }

    void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Input *input = reinterpret_cast<Input *>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            input->keyHeldMap[static_cast<Key>(key)] = true;
            input->keyPressedMap[static_cast<Key>(key)] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            input->keyHeldMap[static_cast<Key>(key)] = false;
            input->keyReleasedMap[static_cast<Key>(key)] = true;
        }
    }

    bool Input::KeyHeld(Key key)
    {
        return keyHeldMap[key];
    }

    bool Input::KeyPressed(Key key)
    {
        return keyPressedMap[key];
    }

    bool Input::KeyReleased(Key key)
    {
        return keyReleasedMap[key];
    }

    void Input::SetMouseMode(MouseMode mode, Window &window)
    {
        glfwSetInputMode(window.window, GLFW_CURSOR, mode);
    }

    void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            mouseHeldMap[button] = true;
            mousePressedMap[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseHeldMap[button] = false;
            mouseReleasedMap[button] = true;
        }
    }

    bool Input::MouseHeld(int button)
    {
        return mouseHeldMap[button];
    }

    bool Input::MousePressed(int button)
    {
        return mousePressedMap[button];
    }

    bool Input::MouseReleased(int button)
    {
        return mouseReleasedMap[button];
    }

    void Input::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
    {
        scrollDelta.x = xoffset;
        scrollDelta.y = yoffset;
    }

    bool Input::JoystickConnected(int joystick)
    {
        return glfwJoystickPresent(joystick);
    }

    std::vector<float> Input::JoystickAxes(int joystick)
    {
        int count;
        const float *axes = glfwGetJoystickAxes(joystick, &count);
        std::vector<float> axesVector(axes, axes + count);
        return axesVector;
    }

    std::vector<unsigned char> Input::JoystickButtons(int joystick)
    {
        int count;
        const unsigned char *buttons = glfwGetJoystickButtons(joystick, &count);
        std::vector<unsigned char> buttonsVector(buttons, buttons + count);
        return buttonsVector;
    }

    std::string Input::GetClipboard(Window &window)
    {
        return glfwGetClipboardString(window.window);
    }

    void Input::SetClipboard(std::string string, Window &window)
    {
        glfwSetClipboardString(window.window, string.c_str());
    }
}