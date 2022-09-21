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
    void Window::ErrorCallback(int code, const char *description)
    {
        std::cout << "GL::ERROR::" << code << ": " << description << std::endl;
    }

    void Window::Init(const Configuration &config)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (config.hideWindow)
            glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        window = glfwCreateWindow(config.windowSize.x, config.windowSize.y, config.windowTitle.c_str(), nullptr, (config.shareContextWith != nullptr) ? config.shareContextWith : nullptr);

        glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glViewport(0, 0, config.windowSize.x, config.windowSize.y);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        glfwSetErrorCallback((GLFWerrorfun)ErrorCallback);

        if (config.drawWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (config.windowIconPath != "")
            SetIcon(config.windowIconPath);

        if (config.vsync)
            glfwSwapInterval(1);
    }

    void Window::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void Window::Terminate()
    {
        glfwTerminate();
    }

    void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(window, true);
    }

    void Window::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    void Window::SetIcon(const std::string &path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLFWimage image;
            image.width = width;
            image.height = height;
            image.pixels = data;
            glfwSetWindowIcon(window, 1, &image);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load icon." << std::endl;
        }
    }

    glm::vec2 Window::GetWindowPos()
    {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return glm::vec2(x, y);
    }

    void Window::SetWindowPos(const glm::vec2 &pos)
    {
        glfwSetWindowPos(window, pos.x, pos.y);
    }

    glm::vec2 Window::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return glm::vec2(width, height);
    }

    void Window::SetWindowSizeLimits(const glm::vec2 &minSize, const glm::vec2 &maxSize)
    {
        glfwSetWindowSizeLimits(window, minSize.x, minSize.y, maxSize.x, maxSize.y);
    }

    void Window::SetWindowAspectRatio(const int &numerator, const int &denominator)
    {
        glfwSetWindowAspectRatio(window, numerator, denominator);
    }

    void Window::SetWindowSize(const glm::vec2 &size)
    {
        glfwSetWindowSize(window, size.x, size.y);
    }

    glm::vec2 Window::GetWindowContentScale()
    {
        float x, y;
        glfwGetWindowContentScale(window, &x, &y);
        return glm::vec2(x, y);
    }

    float Window::GetWindowOpacity()
    {
        return glfwGetWindowOpacity(window);
    }

    void Window::SetWindowOpacity(const float &opacity)
    {
        glfwSetWindowOpacity(window, opacity);
    }

    void Window::IconifyWindow()
    {
        glfwIconifyWindow(window);
    }

    void Window::RestoreWindow()
    {
        glfwRestoreWindow(window);
    }

    void Window::MaximizeWindow()
    {
        glfwMaximizeWindow(window);
    }

    void Window::ShowWindow()
    {
        glfwShowWindow(window);
    }

    void Window::HideWindow()
    {
        glfwHideWindow(window);
    }

    void Window::FocusWindow()
    {
        glfwFocusWindow(window);
    }

    void Window::RequestWindowAttention()
    {
        glfwRequestWindowAttention(window);
    }

    void Window::SetVSync(const bool &vsync)
    {
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }
}