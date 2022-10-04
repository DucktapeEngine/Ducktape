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

namespace DT
{
    bool Input::GetKey(int key)
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::GetKeyPressed(int key)
    {
        return keysDown.find(key) != keysDown.end();
    }

    bool Input::GetKeyReleased(int key)
    {
        return keysUp.find(key) != keysUp.end();
    }

    bool Input::GetMouseButton(int button)
    {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    bool Input::GetMouseButtonPressed(int button)
    {
        return mouseButtonsDown.find(button) != mouseButtonsDown.end();
    }

    bool Input::GetMouseButtonReleased(int button)
    {
        return mouseButtonsUp.find(button) != mouseButtonsUp.end();
    }

    Input::Input(GLFWwindow *_window)
    {
        window = _window;
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
    }

    void Input::Process()
    {
        // Mouse
        double curPosX, curPosY;
        glfwGetCursorPos(window, &curPosX, &curPosY);

        mouseDelta = glm::vec2(curPosX - mousePosition.x, curPosY - mousePosition.y);

        mousePosition = glm::vec2(curPosX, curPosY);

        // Keyboard
        keysUp.clear();
        keysDown.clear();
        mouseButtonsUp.clear();
        mouseButtonsDown.clear();
    }

    void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Input *input = reinterpret_cast<UserPointer *>(glfwGetWindowUserPointer(window))->input;

        if (action == GLFW_PRESS)
            input->keysDown.insert(key);
        else if (action == GLFW_RELEASE)
            input->keysUp.insert(key);
    }

    void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Input *input = reinterpret_cast<UserPointer *>(glfwGetWindowUserPointer(window))->input;

        if (action == GLFW_PRESS)
            input->mouseButtonsDown.insert(button);
        else if (action == GLFW_RELEASE)
            input->mouseButtonsUp.insert(button);
    }
}