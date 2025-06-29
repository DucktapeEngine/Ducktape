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

namespace DT
{
    class Window;
    class Renderer;
    class Panel;

    class Editor
    {
    public:
        Editor(Context &ctx);
        ~Editor();

        void Init(Context &ctx);
        void NewFrame();
        void Tick(Context &ctx, const float &dt);
        void EndFrame();

        void Close();
        void SetTitle(const std::string &title);
        glm::vec2 GetWindowPos();
        void SetWindowPos(const glm::vec2 &pos);
        glm::vec2 GetWindowSize();
        void SetWindowSizeLimits(const glm::vec2 &minSize, const glm::vec2 &maxSize);
        void SetWindowAspectRatio(const int &numerator, const int &denominator);
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
        void SetupImGuiStyle();

        template <typename T>
        void AttachPanel(T *panel)
        {
            panels[std::type_index(typeid(T))] = panel;
            panel->editor = this;
        }

        template <typename T>
        T *GetPanel()
        {
            return (T *)panels[std::type_index(typeid(T))];
        }

    private:
        Window *window;
        Renderer *renderer;

        ImGuiID dockspaceId;
        std::unordered_map<std::type_index, Panel *> panels;
    };
}