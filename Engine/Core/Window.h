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

#pragma once

#include <Core/Serialization.h>
#include <Core/Context.h>

#define CURSOR_MODE_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_MODE_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_MODE_DISABLED GLFW_CURSOR_DISABLED

namespace DT
{
    class Error;

    class Window
    {
    public:
        Window(Context &ctx, const json &windowData, Error *err);
        ~Window();

        GLFWwindow *GetRawWindowPointer()
        {
            PROFILE();

            return window;
        }

        bool IsOpen()
        {
            PROFILE();

            return !glfwWindowShouldClose(window);
        }

        void PollEvents()
        {
            PROFILE();

            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                Close();
        }

        void SwapBuffers()
        {
            PROFILE();

            glfwSwapBuffers(window);
        }

        void Close();
        void SetTitle(const std::string &title);
        glm::vec2 GetWindowPos();
        void SetWindowPos(const glm::vec2 &pos);
        glm::vec2 GetWindowSize();
        void SetWindowSize(const glm::vec2 &size);
        glm::vec2 GetWindowContentScale();
        float GetWindowOpacity();
        void SetWindowOpacity(const float &opacity);
        void IconifyWindow();
        void RestoreWindow();
        void MaximizeWindow();
        void ShowWindow();
        void HideWindow();
        void FocusWindow();
        void RequestWindowAttention();
        void SetVSync(const bool &vsync);
        bool IsFocused();
        void SetInputCursorMode(int mode);
        
        static void ErrorCallback(int code, const char *description);
        static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);

    private:
        GLFWwindow *window = nullptr;
        glm::vec2 windowSize;
    };
}