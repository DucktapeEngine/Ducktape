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

#include <Panels/Panel.h>
#include <EditorCamera.h>
#include <Panels/WorldOutliner.h>

namespace DT
{
    class WorldViewPanel : public Panel
    {
    public:
        EditorCamera editorCamera;

        WorldViewPanel(Context &ctx) : editorCamera(&ctx),
                                       translateIcon(Texture::Load(ctx.projectPath / "Engine" / "Icons" / "translate.png").Fatal("WorldViewPanel::WorldViewPanel()")),
                                       rotateIcon(Texture::Load(ctx.projectPath / "Engine" / "Icons" / "rotate.png").Fatal("WorldViewPanel::WorldViewPanel()")),
                                       scaleIcon(Texture::Load(ctx.projectPath / "Engine" / "Icons" / "scale.png").Fatal("WorldViewPanel::WorldViewPanel()")) {}

        void Init(Context &ctx) override
        {
            PROFILE();

            renderer = ctx.GetService<Renderer>().Fatal("WorldViewPanel::Init()");
            window = ctx.GetService<Window>().Fatal("WorldViewPanel::Init()");
            sceneManager = ctx.GetService<SceneManager>().Fatal("WorldViewPanel::Init()");
            input = ctx.GetService<InputManager>().Fatal("WorldViewPanel::Init()");
            worldOutliner = editor->GetPanel<WorldOutlinerPanel>().Fatal("WorldViewPanel::Init()");

            input->OnKeyEvent(KEY_T, [&](int action)
                              { gizmoOperation = ImGuizmo::TRANSLATE; });
            input->OnKeyEvent(KEY_R, [&](int action)
                              { gizmoOperation = ImGuizmo::ROTATE; });
            input->OnKeyEvent(KEY_E, [&](int action)
                              { gizmoOperation = ImGuizmo::SCALE; });

            ImGuizmo::AllowAxisFlip(false);
        }

        void Tick(Context &ctx, const float &dt) override
        {
            PROFILE();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
            ImGui::Begin("World View", &isOpen);

            worldViewActive = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
            ImVec2 vMin = ImGui::GetWindowContentRegionMin();
            ImVec2 vMax = ImGui::GetWindowContentRegionMax();

            vMin.x += ImGui::GetWindowPos().x;
            vMin.y += ImGui::GetWindowPos().y;
            vMax.x += ImGui::GetWindowPos().x;
            vMax.y += ImGui::GetWindowPos().y;

            windowPos = vMin;

            ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

            if (window->GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
            {
                if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
                {
                    window->SetWindowSize({windowSize.x, windowSize.y});
                    renderer->SetViewport({windowSize.x, windowSize.y});
                }
            }

            // Freelook
            if (!isFreeLookActive && worldViewActive && input->IsMouseButtonHeld(MOUSE_BUTTON_RIGHT))
            {
                window->SetInputCursorMode(CURSOR_MODE_DISABLED);
                isFreeLookActive = true;
            }
            if (isFreeLookActive && !input->IsMouseButtonHeld(MOUSE_BUTTON_RIGHT))
            {
                window->SetInputCursorMode(CURSOR_MODE_NORMAL);
                isFreeLookActive = false;
            }

            if (isFreeLookActive)
                FreeLook(dt);
            if (worldViewActive || isFreeLookActive)
                FreeMove(dt);

            // Render
            ImGui::GetWindowDrawList()->AddImage(
                (ImTextureID)(uintptr_t)editorCamera.renderTexture,
                vMin,
                vMax,
                ImVec2(0, 1),
                ImVec2(1, 0));

            // Manipulate
            ImGuizmo::SetDrawlist();
            ImGuizmo::DrawGrid(glm::value_ptr(editorCamera.view), glm::value_ptr(editorCamera.projection), glm::value_ptr(glm::mat4(1.f)), 10.f);

            ImGuizmo::SetOrthographic(editorCamera.isOrthographic);
            ImGuizmo::SetRect(vMin.x, vMin.y, window->GetWindowSize().x, window->GetWindowSize().y);

            float snap = 1.f;
            if (gizmoOperation == ImGuizmo::OPERATION::ROTATE)
                snap = 45.f;

            Entity selectedEntity = worldOutliner->GetSelectedEntity();
            if (sceneManager->activeScene.IsValid(selectedEntity) != 0 && sceneManager->activeScene.Has<Transform>(selectedEntity))
            {
                std::shared_ptr<Transform> transform = sceneManager->activeScene.Get<Transform>(selectedEntity).Fatal("WorldView::Tick()");
                glm::mat4 model = transform->GetModelMatrix();

                ImGuizmo::Manipulate(glm::value_ptr(editorCamera.view), glm::value_ptr(editorCamera.projection), gizmoOperation, currentGizmoMode, glm::value_ptr(model), NULL, input->IsKeyHeld(KEY_LEFT_CONTROL) ? &snap : NULL);

                if (ImGuizmo::IsUsing())
                    transform->SetModelMatrix(model);
            }

            ImGui::End();
            ImGui::PopStyleVar();

            RenderToolbarPanel();
        }

    private:
        bool worldViewActive;
        ImVec2 windowPos, windowSize;

        bool isFreeLookActive = false;
        glm::vec3 orientation;
        float speed = 2.5f, sensitivity = 50.f;
        float lastx;

        bool freeLook2DMode = false;
        Texture translateIcon, rotateIcon, scaleIcon;
        ImGuizmo::OPERATION gizmoOperation = ImGuizmo::TRANSLATE;
        ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;

        Renderer *renderer;
        Window *window;
        SceneManager *sceneManager;
        InputManager *input;
        WorldOutlinerPanel *worldOutliner;

        void FreeMove(const float &dt)
        {
            if (freeLook2DMode)
                editorCamera.transform.SetEulerRotation({0.f, 180.f, 0.f});

            if (input->IsKeyHeld(KEY_W))
                editorCamera.transform.translation += speed * dt * editorCamera.transform.Forward();
            if (input->IsKeyHeld(KEY_A))
                editorCamera.transform.translation -= speed * dt * editorCamera.transform.Right();
            if (input->IsKeyHeld(KEY_S))
                editorCamera.transform.translation -= speed * dt * editorCamera.transform.Forward();
            if (input->IsKeyHeld(KEY_D))
                editorCamera.transform.translation += speed * dt * editorCamera.transform.Right();
            if (input->IsKeyHeld(KEY_SPACE))
                editorCamera.transform.translation += speed * dt * glm::vec3(0.f, 1.f, 0.f);
            if (input->IsKeyHeld(KEY_LEFT_SHIFT))
                editorCamera.transform.translation -= speed * dt * glm::vec3(0.f, 1.f, 0.f);
        }

        void FreeLook(const float &dt)
        {
            orientation.y += input->GetMouseDelta().x * sensitivity * dt;
            orientation.x += -input->GetMouseDelta().y * sensitivity * dt;

            if (orientation.x < -90.0f)
                orientation.x = -90.0f;
            if (orientation.x > 90.0f)
                orientation.x = 90.0f;

            orientation = glm::angNormalize(orientation);
            editorCamera.transform.SetEulerRotation(orientation);
        }

        void RenderToolbarPanel()
        {
            const float padding = 10.f;
            const float iconSize = 25.f;

            ImGui::SetNextWindowPos(ImVec2(windowPos.x + padding, windowPos.y + padding));

            ImGuiWindowFlags windowFlags = 0 | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
            ImGui::Begin("Tool Bar", NULL, windowFlags);
            ImGui::PopStyleVar();

            // Transform control
            ImGuizmo::OPERATION currentGizmoOperation = gizmoOperation;

            if (currentGizmoOperation == ImGuizmo::TRANSLATE)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            }
            if (ImGui::ImageButton((ImTextureID)(uintptr_t)translateIcon.id, ImVec2(iconSize, iconSize)))
                gizmoOperation = ImGuizmo::TRANSLATE;
            if (currentGizmoOperation == ImGuizmo::TRANSLATE)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }

            if (currentGizmoOperation == ImGuizmo::ROTATE)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            }
            ImGui::SameLine();
            if (ImGui::ImageButton((ImTextureID)(uintptr_t)rotateIcon.id, ImVec2(iconSize, iconSize)))
                gizmoOperation = ImGuizmo::ROTATE;
            if (currentGizmoOperation == ImGuizmo::ROTATE)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }

            if (currentGizmoOperation == ImGuizmo::SCALE)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            }
            ImGui::SameLine();
            if (ImGui::ImageButton((ImTextureID)(uintptr_t)scaleIcon.id, ImVec2(iconSize, iconSize)))
                gizmoOperation = ImGuizmo::SCALE;
            if (currentGizmoOperation == ImGuizmo::SCALE)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }

            ImGui::SameLine();
            ImGui::Checkbox("Orthographic", &editorCamera.isOrthographic);
            ImGui::SameLine();
            ImGui::Checkbox("2D", &freeLook2DMode);

            // Runtime state control
            // RuntimeState currentRuntimeState = runtimeState;

            // if (currentRuntimeState == RuntimeState::Play)
            // {
            //     ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            // }
            // if (ImGui::ImageButton((ImTextureID)(uintptr_t)playIconId, ImVec2(iconSize, iconSize)))
            // {
            //     runtimeState = RuntimeState::Play;
            //     ctx.loopManager->gameTick = true;
            // }
            // if (currentRuntimeState == RuntimeState::Play)
            // {
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            // }

            // if (currentRuntimeState == RuntimeState::Pause)
            // {
            //     ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            // }
            // if (ImGui::ImageButton((ImTextureID)(uintptr_t)pauseIconId, ImVec2(iconSize, iconSize)))
            // {
            //     runtimeState = RuntimeState::Pause;
            //     ctx.loopManager->gameTick = false;
            // }
            // if (currentRuntimeState == RuntimeState::Pause)
            // {
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            // }

            // if (currentRuntimeState == RuntimeState::Stop)
            // {
            //     ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            // }
            // if (ImGui::ImageButton((ImTextureID)(uintptr_t)stopIconId, ImVec2(iconSize, iconSize)))
            // {
            //     runtimeState = RuntimeState::Stop;
            //     ctx.loopManager->gameTick = false;
            //     ctx.loopManager->sceneTick = true;
            // }
            // if (currentRuntimeState == RuntimeState::Stop)
            // {
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            //     ImGui::PopStyleColor();
            // }

            ImGui::End();
        }
    };
}