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

#include <Input/Key.h>
#include <Core/Context.h>
#include <Core/Serialization.h>

#include <Input/Input.h>

namespace DT
{
    Input::Input(ContextPtr &ctx)
    {
        window = ctx.window->window;
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);

        std::cout << "[LOG] Input Constructed\n";
    }

    void Input::Process()
    {
        // Mouse
        double curPosX, curPosY;
        glfwGetCursorPos(window, &curPosX, &curPosY);

        mouseDelta = glm::vec2(curPosX - mousePosition.x, curPosY - mousePosition.y);
        mousePosition = glm::vec2(curPosX, curPosY);
    }

    bool Input::IsKeyHeld(Key key)
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonHeld(Button button)
    {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    void Input::OnKeyEvent(std::function<void(Key, Action)> onKeyEvent)
    {
        onKeyEvents.push_back(onKeyEvent);
    }

    void Input::OnMouseEvent(std::function<void(Button, Action)> onMouseEvent)
    {
        onMouseEvents.push_back(onMouseEvent);
    }

    void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        UNUSED(scancode);
        UNUSED(mods);
        Input *input = reinterpret_cast<ContextPtr *>(glfwGetWindowUserPointer(window))->input;

        for (auto &onKeyEvent : input->onKeyEvents)
            onKeyEvent(key, action);
    }

    void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        UNUSED(mods);
        Input *input = reinterpret_cast<ContextPtr *>(glfwGetWindowUserPointer(window))->input;

        for (auto &onMouseEvent : input->onMouseEvents)
            onMouseEvent(button, action);
    }
}
