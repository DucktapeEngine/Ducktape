/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#include <Core/Error.h>
#include <Core/Window.h>

namespace DT
{
    Window::Window(Context &ctx, const json &windowData, Error *err)
    {
        PROFILE();

        bool hideWindow = windowData.value("hideWindow", false);
        windowSize = windowData.value("windowSize", glm::vec2(1024.f, 600.f));
        std::string windowTitle = windowData.value("windowTitle", "Ducktape Project");
        bool drawWireframe = windowData.value("drawWireframe", false);
        std::filesystem::path windowIconPath = windowData.value("windowIconPath", std::filesystem::path());
        bool vsync = windowData.value("vsync", true);
        
        glfwInit();

        glfwSetErrorCallback((GLFWerrorfun)ErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        glfwWindowHint(GLFW_VISIBLE, !hideWindow);

#ifdef __APPLE_
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

        window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.c_str(), nullptr, nullptr);
        if (window == nullptr)
        {
            *err = Error("Failed to create GLFW window.\n");
            return;
        }
        std::cout << "[LOG] Created GLFW Window.\n";

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            *err = Error("Failed to initialize GLAD.\n");
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

        glViewport(0, 0, windowSize.x, windowSize.y);
        glPolygonMode(GL_FRONT_AND_BACK, drawWireframe ? GL_LINE : GL_FILL);

        // if (!windowIconPath.empty())
        //     SetIcon(windowIconPath);

        if (vsync)
            glfwSwapInterval(0);

        glfwSetWindowUserPointer(window, reinterpret_cast<void *>(&ctx));

        std::cout << "[LOG] Window Constructed.\n";
    }

    Window::~Window()
    {
        PROFILE();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::Close()
    {
        PROFILE();

        glfwSetWindowShouldClose(window, true);
    }

    void Window::SetTitle(const std::string &title)
    {
        PROFILE();

        glfwSetWindowTitle(window, title.c_str());
    }

    glm::vec2 Window::GetWindowPos()
    {
        PROFILE();

        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return glm::vec2(x, y);
    }

    void Window::SetWindowPos(const glm::vec2 &pos)
    {
        PROFILE();

        glfwSetWindowPos(window, pos.x, pos.y);
    }

    glm::vec2 Window::GetWindowSize()
    {
        PROFILE();

#ifdef DT_EXPORT
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return glm::vec2(width, height);
#else
        return windowSize;
#endif
    }

    void Window::SetWindowSize(const glm::vec2 &size)
    {
        PROFILE();

#ifdef DT_EXPORT
        glfwSetWindowSize(window, size.x, size.y);
#else
        windowSize = size;
#endif
        glViewport(0, 0, size.x, size.y);
    }

    glm::vec2 Window::GetWindowContentScale()
    {
        PROFILE();

        float x, y;
        glfwGetWindowContentScale(window, &x, &y);
        return glm::vec2(x, y);
    }

    float Window::GetWindowOpacity()
    {
        PROFILE();

        return glfwGetWindowOpacity(window);
    }

    void Window::SetWindowOpacity(const float &opacity)
    {
        PROFILE();

        glfwSetWindowOpacity(window, opacity);
    }

    void Window::IconifyWindow()
    {
        PROFILE();

        glfwIconifyWindow(window);
    }

    void Window::RestoreWindow()
    {
        PROFILE();

        glfwRestoreWindow(window);
    }

    void Window::MaximizeWindow()
    {
        PROFILE();

        glfwMaximizeWindow(window);
    }

    void Window::ShowWindow()
    {
        PROFILE();

        glfwShowWindow(window);
    }

    void Window::HideWindow()
    {
        PROFILE();

        glfwHideWindow(window);
    }

    void Window::FocusWindow()
    {
        PROFILE();

        glfwFocusWindow(window);
    }

    void Window::RequestWindowAttention()
    {
        PROFILE();

        glfwRequestWindowAttention(window);
    }

    void Window::SetVSync(const bool &vsync)
    {
        PROFILE();

        glfwSwapInterval(vsync);
    }

    bool Window::IsFocused()
    {
        PROFILE();

        return glfwGetWindowAttrib(window, GLFW_FOCUSED);
    }

    void Window::SetInputCursorMode(int mode)
    {
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }

    void Window::ErrorCallback(int code, const char *description)
    {
        PROFILE();

        std::cout << "[ERR] [OPENGL] [" << code << "] " << description << "\n";
    }
    
    void APIENTRY Window::GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
    {
        PROFILE();

        // UNUSED(length);
        // UNUSED(userParam);

        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        std::string err;
        
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            err += "[FATAL] [ID:" + std::to_string(id) + "] ";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            err += "[ERR] [ID:" + std::to_string(id) + "] ";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            err += "[WARN] [ID:" + std::to_string(id) + "] ";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            err += "[NOTE] [ID:" + std::to_string(id) + "] ";
            break;
        }

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            err += "[API] ";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            err += "[Window System] ";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            err += "[Shader Compiler] ";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            err += "[Third Party] ";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            err += "[Application] ";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            err += "[Other] ";
            break;
        }

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            err += "[Error] ";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            err += "[Deprecated Behaviour] ";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            err += "[Undefined Behaviour] ";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            err += "[Portability] ";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            err += "[Performance] ";
            break;
        case GL_DEBUG_TYPE_MARKER:
            err += "[Marker] ";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            err += "[Push Group] ";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            err += "[Pop Group] ";
            break;
        case GL_DEBUG_TYPE_OTHER:
            err += "[Other] ";
            break;
        }

        std::cout << err << "\n" << message << "\n";
    }
}