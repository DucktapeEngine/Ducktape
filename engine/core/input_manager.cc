/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

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

#include <glm/gtx/string_cast.hpp>
#include <core/input_manager.h>

namespace DT
{
    InputManager::InputManager(Context &ctx)
    {
        window = ctx.GetService<Window>();

        glfwSetKeyCallback(window->GetRawWindowPointer(), KeyCallback);
        glfwSetMouseButtonCallback(window->GetRawWindowPointer(), MouseButtonCallback);

        glfwPollEvents();

        double curPosX, curPosY;
        glfwGetCursorPos(window->GetRawWindowPointer(), &curPosX, &curPosY);
        mousePosition = glm::vec2(curPosX, curPosY);

        std::cout << "InputManager Constructed\n";
    }

    void InputManager::Process()
    {
        double curPosX, curPosY;
        glfwGetCursorPos(window->GetRawWindowPointer(), &curPosX, &curPosY);

        mouseDelta = glm::vec2(curPosX - mousePosition.x, mousePosition.y - curPosY);
        mousePosition = glm::vec2(curPosX, curPosY);
    }

    void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        InputManager *inputManager = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window))->GetService<InputManager>();

        for (auto &onKeyEvent : inputManager->keyEvents[key])
            onKeyEvent(action);
    }

    void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        InputManager *inputManager = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window))->GetService<InputManager>();

        for (auto &onMouseEvent : inputManager->mouseEvents[button])
            onMouseEvent(action);
    }
}