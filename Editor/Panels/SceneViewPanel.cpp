#include "SceneViewPanel.h"

namespace DT
{
    void SceneViewPanel::Update(Engine &engine)
    {
        selectedEntity = engine.activeScene->selectedEntity;
        if(sceneViewActive)
        {
            // Controls
            // Move
            const float speed = 2.5f, sensitivity = 25.f;
            bool holdingRightButton = engine.input.GetMouseButton(MOUSE_BUTTON_RIGHT);

            if (holdingRightButton && engine.input.GetKey(KEY_W))
                engine.activeScene->activeCamera->transform->translation += speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Forward();
            if (holdingRightButton && engine.input.GetKey(KEY_S))
                engine.activeScene->activeCamera->transform->translation -= speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Forward();
            if (holdingRightButton && engine.input.GetKey(KEY_A))
                engine.activeScene->activeCamera->transform->translation += speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Right();
            if (holdingRightButton && engine.input.GetKey(KEY_D))
                engine.activeScene->activeCamera->transform->translation -= speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Right();

            // Look
            if (holdingRightButton)
            {
                yaw += -engine.input.mouseDelta.x * sensitivity * engine.time.deltaTime;
                pitch += engine.input.mouseDelta.y * sensitivity * engine.time.deltaTime;

                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }
        }
        engine.activeScene->activeCamera->transform->rotation = glm::quat({ pitch * DEG2RAD, yaw * DEG2RAD, 0.0f });
        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin("Scene View");
        sceneViewActive = ImGui::IsWindowFocused();
        // ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

        if (engine.window.GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
        {
            if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
            {
                engine.window.SetWindowSize({ windowSize.x, windowSize.y });
                engine.renderer.SetViewport({ windowSize.x, windowSize.y });
            }
        }

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(uintptr_t)engine.renderer.renderTexture,
            vMin,
            vMax,
            ImVec2(0, 1),
            ImVec2(1, 0));

        if (selectedEntity != entt::null && engine.activeScene->Has<Transform>(selectedEntity))
        {
            Transform& transform = engine.activeScene->Get<Transform>(selectedEntity);

            glm::mat4 model = transform.GetModelMatrix();

            ImGuizmo::SetOrthographic(engine.activeScene->activeCamera->isOrtho);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, engine.window.GetWindowSize().x, engine.window.GetWindowSize().y);

            float snap = 1.f;
            if (currentGizmoOperation == ImGuizmo::OPERATION::ROTATE)
                snap = 45.f;

            ImGuizmo::Manipulate(glm::value_ptr(engine.activeScene->activeCamera->view), glm::value_ptr(engine.activeScene->activeCamera->projection), currentGizmoOperation, currentGizmoMode, glm::value_ptr(model), NULL, engine.input.GetKey(KEY_LEFT_SHIFT) ? &snap : NULL);

            if (ImGuizmo::IsUsing())
            {
                transform.SetModelMatrix(model);
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        RenderToolbarPanel(engine);
    }

    void SceneViewPanel::RenderToolbarPanel(Engine &engine)
    {
        ImGui::Begin("Tool Bar");

        bool holdingRightButton = engine.input.GetMouseButton(MOUSE_BUTTON_RIGHT);

        if (!holdingRightButton && engine.input.GetKeyPressed(KEY_T))
            currentGizmoOperation = ImGuizmo::TRANSLATE;
        if (!holdingRightButton && engine.input.GetKeyPressed(KEY_R))
            currentGizmoOperation = ImGuizmo::ROTATE;
        if (!holdingRightButton && engine.input.GetKeyPressed(KEY_S))
            currentGizmoOperation = ImGuizmo::SCALE;
        if (ImGui::RadioButton("translate", currentGizmoOperation == ImGuizmo::TRANSLATE))
            currentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("rotate", currentGizmoOperation == ImGuizmo::ROTATE))
            currentGizmoOperation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("scale", currentGizmoOperation == ImGuizmo::SCALE))
            currentGizmoOperation = ImGuizmo::SCALE;

        if (ImGui::RadioButton("local", currentGizmoMode == ImGuizmo::LOCAL))
            currentGizmoMode = ImGuizmo::LOCAL;
        ImGui::SameLine();
        if (ImGui::RadioButton("world", currentGizmoMode == ImGuizmo::WORLD))
            currentGizmoMode = ImGuizmo::WORLD;

        ImGui::End();
    }
}
