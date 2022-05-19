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

#include <Core/Window.h>

namespace Ducktape
{
    void Window::Init(const Configuration &config)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        windowSize = config.windowSize;
        window = glfwCreateWindow(windowSize.x, windowSize.y, config.windowTitle.c_str(), NULL, NULL);
        glfwSetWindowUserPointer(window, this);

        if (window == NULL)
        {
            throw std::runtime_error("Failed to create GLFW window.");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD.");
        }

        glEnable(GL_DEPTH_TEST);
    }

    void Window::Tick()
    {
        glfwPollEvents();
    }

    void Window::Cleanup()
    {
        glfwTerminate();
    }

    void Window::FrameBufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
        static_cast<Window *>(glfwGetWindowUserPointer(window))->windowSize = glm::vec2(width, height);
    }
}