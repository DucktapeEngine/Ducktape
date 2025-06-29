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

#include <core/window.h>
#include <core/log.h>

namespace DT
{
    Window::Window(Context &ctx)
    {
        glfwInit();

        glfwSetErrorCallback((GLFWerrorfun)ErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE_
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

        m_Window = glfwCreateWindow(1920, 1080, "Ducktape Engine", nullptr, nullptr);
        if (m_Window == nullptr)
        {
            ERROR("Failed to create GLFW window.");
            return;
        }
        LOG("Created GLFW Window.");

        glfwMakeContextCurrent(m_Window);

        // TODO: perhaps move this whole thing to Renderer
        {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                ERROR("Failed to initialize GLAD.");
                return;
            }
            LOG("Initialized GLAD.");

            int flags;
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
            {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback(GlDebugOutput, nullptr);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            }

            glViewport(0, 0, m_WindowSize.x, m_WindowSize.y);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // also check what the default value is
        }

        SetVSyncEnabled(true);
        glfwSetWindowUserPointer(m_Window, reinterpret_cast<void *>(&ctx));

        m_WindowInitalized = true;
        LOG("Window constructed.");
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::ErrorCallback(int code, const char *description)
    {
        ERROR("[GLFW] [{}] {}", code, description);
    }

    // TODO: move to Renderer
    void APIENTRY Window::GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
    {
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
            err += "[ID:" + std::to_string(id) + "] ";
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

        std::cout << err << "\n"
                  << message << "\n";
    }
}