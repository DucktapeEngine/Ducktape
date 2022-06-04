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

namespace DT
{
    void Window::Init()
    {
        FT("Window::Init()");

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(Configuration::windowSize.x, Configuration::windowSize.y, Configuration::windowTitle.c_str(), nullptr, nullptr);
        if (window == nullptr)
        {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, Configuration::windowSize.x, Configuration::windowSize.y);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

        if (Configuration::drawWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // copilot do the trick, make a vsync
        if (Configuration::vsync)
            glfwSwapInterval(1);
    }

    void Window::Clear(Color color)
    {
        FT("Window::Clear()");

        glm::vec4 clearColor = glm::vec4(color.r, color.g, color.b, color.a);
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::PollEvents()
    {
        FT("Window::PollEvents()");

        glfwPollEvents();
    }

    void Window::Display()
    {
        FT("Window::Display()");

        glfwSwapBuffers(window);
    }

    void Window::Destroy()
    {
        FT("Window::Destroy()");

        glfwTerminate();
    }

    void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        FT("Window::FramebufferSizeCallback()");

        glViewport(0, 0, width, height);
    }
}