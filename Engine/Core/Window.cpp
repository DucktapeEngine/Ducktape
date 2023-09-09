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

#include <vector>
#include <stdexcept>
#include <iostream>

#include <imgui/imgui.h>
#include <utils/stb_image.h>

#include <Core/Serialization.h>
#include <Core/Window.h>
#include <Core/Macro.h>

namespace DT
{
    void APIENTRY Window::GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
    {
        UNUSED(length);
        UNUSED(userParam);
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        std::cout << "[ERR] [ID:" << id << "] ";

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            std::cout << "[API]";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "[Window System]";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "[Shader Compiler]";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "[Third Party]";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "[Application]";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "[Other]";
            break;
        }
        std::cout << " ";

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "[Error]";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "[Deprecated Behaviour]";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "[Undefined Behaviour]";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "[Portability]";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "[Performance]";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "[Marker]";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "[Push Group]";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "[Pop Group]";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "[Other]";
            break;
        }
        std::cout << " ";

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "[FATAL]";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "[ERR]";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "[WARN]";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "[NOTE]";
            break;
        }

        std::cout << " " << message << std::endl;
    }

    void Window::ErrorCallback(int code, const char *description)
    {
        std::cout << "[ERR] [OPENGL] [" << code << "] " << description << std::endl;
    }

    Window::Window(const json &data, ContextPtr &ctx) : hideWindow(data["hideWindow"]), windowSize(data["windowSize"]), windowTitle(data["windowTitle"]), drawWireframe(data["drawWireframe"]), windowIconPath(data["windowIconPath"]), vsync(data["vsync"])
    {
        glfwInit();

        glfwSetErrorCallback((GLFWerrorfun)ErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        if (hideWindow)
            glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
        else
            glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

        window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            std::cout << "[ERR] Failed to create GLFW window\n";
            return;
        }
        std::cout << "[LOG] Created GLFW Window.\n";

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "[ERR] Failed to initialize GLAD\n";
            return;
        }
        std::cout << "[LOG] Initialized GLAD.\n";

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(GlDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        windowSize = windowSize;
        glViewport(0, 0, windowSize.x, windowSize.y);

        if (drawWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (windowIconPath != "")
            SetIcon(windowIconPath);

        if (vsync)
            glfwSwapInterval(1);

        glfwSetWindowUserPointer(window, reinterpret_cast<void *>(&ctx));

        std::cout << "[LOG] Window Constructed\n";
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

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(window, true);
    }

    void Window::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    void Window::SetIcon(std::filesystem::path path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
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
            std::cout << "[LOG] Failed to load window icon.\n";
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
        return windowSize;
    }

    void Window::SetWindowSize(const glm::vec2 &size)
    {
        windowSize = size;
        glViewport(0, 0, size.x, size.y);
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

    bool Window::GetMinimized()
    {
        return !glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
    }
}
