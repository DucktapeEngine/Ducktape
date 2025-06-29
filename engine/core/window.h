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

#pragma once

#include <GLFW/glfw3.h>
#include <core/serialization.h>
#include <core/context.h>

#define CURSOR_MODE_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_MODE_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_MODE_DISABLED GLFW_CURSOR_DISABLED

namespace DT
{
    class Window
    {
    private:
        bool m_WindowInitalized = false;
        GLFWwindow *m_Window = nullptr;
        glm::vec2 m_WindowSize;

    public:
        Window(Context &ctx);
        ~Window();

        inline GLFWwindow *GetRawWindowPointer()
        {
            return m_Window;
        }

        inline bool IsOpen() // TODO: name doesn't feel right
        {
            return !glfwWindowShouldClose(m_Window);
        }

        inline void PollEvents()
        {
            glfwPollEvents();
            if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // TODO: handling somewhere else seems more appropriate
                Close();
        }

        inline void SwapBuffers()
        {
            glfwSwapBuffers(m_Window);
        }

        inline void Close()
        {
            glfwSetWindowShouldClose(m_Window, true);
        }

        inline void SetTitle(const std::string &title)
        {
            glfwSetWindowTitle(m_Window, title.c_str());
        }

        inline glm::vec2 GetWindowPos()
        {
            int x, y;
            glfwGetWindowPos(m_Window, &x, &y);
            return glm::vec2(x, y);
        }

        inline void SetWindowPos(const glm::vec2 &pos)
        {
            glfwSetWindowPos(m_Window, pos.x, pos.y);
        }

        inline glm::vec2 GetWindowSize()
        {
#ifdef DT_EXPORT
            int width, height;
            glfwGetWindowSize(m_Window, &width, &height);
            return glm::vec2(width, height);
#else
            return m_WindowSize;
#endif
        }

        inline void SetWindowSize(const glm::vec2 &size)
        {
#ifdef DT_EXPORT
            glfwSetWindowSize(m_Window, size.x, size.y);
#else
            m_WindowSize = size;
#endif
            glViewport(0, 0, size.x, size.y);
        }

        inline glm::vec2 GetWindowContentScale()
        {
            float x, y;
            glfwGetWindowContentScale(m_Window, &x, &y);
            return glm::vec2(x, y);
        }

        inline float GetWindowOpacity()
        {
            return glfwGetWindowOpacity(m_Window);
        }

        inline void SetWindowOpacity(const float &opacity)
        {
            glfwSetWindowOpacity(m_Window, opacity);
        }

        inline void IconifyWindow()
        {
            glfwIconifyWindow(m_Window);
        }

        inline void RestoreWindow()
        {
            glfwRestoreWindow(m_Window);
        }

        inline void MaximizeWindow()
        {
            glfwMaximizeWindow(m_Window);
        }

        inline void ShowWindow()
        {
            glfwShowWindow(m_Window);
        }

        inline void HideWindow()
        {
            glfwHideWindow(m_Window);
        }

        inline void FocusWindow()
        {
            glfwFocusWindow(m_Window);
        }

        inline void RequestWindowAttention()
        {
            glfwRequestWindowAttention(m_Window);
        }

        inline void SetVSyncEnabled(bool enabled)
        {
            glfwSwapInterval(enabled);
        }

        inline bool IsFocused()
        {
            return glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
        }

        inline void SetInputCursorMode(int mode)
        {
            glfwSetInputMode(m_Window, GLFW_CURSOR, mode);
        }

        static void ErrorCallback(int code, const char *description);
        static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
    };
}