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

#include <scene/scene_manager.h>
#include <panels/panel.h>

namespace DT
{
    class GameViewPanel : public Panel
    {
    public:
        void Init(Context &ctx) override
        {
            isOpen = false;

            renderer = ctx.GetService<Renderer>();
            window = ctx.GetService<Window>();
        }

        void Tick(Context &ctx, const float &dt) override
        {
            /// Proper Game Runtime to be implemented in the future
            // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
            // ImGui::Begin("Game View", &isOpen);

            // sceneViewActive = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
            // ImVec2 vMin = ImGui::GetWindowContentRegionMin();
            // ImVec2 vMax = ImGui::GetWindowContentRegionMax();

            // vMin.x += ImGui::GetWindowPos().x;
            // vMin.y += ImGui::GetWindowPos().y;
            // vMax.x += ImGui::GetWindowPos().x;
            // vMax.y += ImGui::GetWindowPos().y;

            // windowPos = vMin;

            // ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

            // if (window->GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
            // {
            //     if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
            //     {
            //         window->SetWindowSize({windowSize.x, windowSize.y});
            //         renderer->SetViewport({windowSize.x, windowSize.y});
            //     }
            // }

            // ImGui::GetWindowDrawList()->AddImage(
            //     (ImTextureID)(uintptr_t)Camera::GetActiveCamera()->renderTexture,
            //     vMin,
            //     vMax,
            //     ImVec2(0, 1),
            //     ImVec2(1, 0));

            // ImGui::End();
            // ImGui::PopStyleVar();
        }

    private:
        std::shared_ptr<Camera> viewCamera;
        bool sceneViewActive;
        ImVec2 windowPos, windowSize;

        Renderer *renderer;
        Window *window;
    };
}