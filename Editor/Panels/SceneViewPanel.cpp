#include <Panels/SceneViewPanel.h>

namespace DT
{
    void SceneViewPanel::Start(Engine &engine)
    {
        translateIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "translate.png"))->id;
        rotateIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "rotate.png"))->id;
        scaleIconId = Texture::LoadResource(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "scale.png"))->id;

        engine.input.OnKeyEvent([&](Key key, Action action)
                                {
                                    if (key == KEY_T && action == PRESS)
                                        gizmoOperation = ImGuizmo::TRANSLATE;
                                    if (key == KEY_R && action == PRESS)
                                        gizmoOperation = ImGuizmo::ROTATE;
                                    if (key == KEY_S && action == PRESS)
                                        gizmoOperation = ImGuizmo::SCALE; });
    }

    void SceneViewPanel::Update(Engine &engine)
    {
        selectedEntity = engine.activeScene->selectedEntity;
        if (sceneViewActive && engine.activeScene->activeCamera != nullptr)
        {
            // Controls
            // Move
            const float speed = 2.5f, sensitivity = 25.f;
            bool holdingRightButton = engine.input.IsMouseButtonHeld(MOUSE_BUTTON_RIGHT);

            if (engine.input.IsKeyHeld(KEY_UP))
                engine.activeScene->activeCamera->transform->translation += speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Forward();
            if (engine.input.IsKeyHeld(KEY_DOWN))
                engine.activeScene->activeCamera->transform->translation -= speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Forward();
            if (engine.input.IsKeyHeld(KEY_LEFT))
                engine.activeScene->activeCamera->transform->translation += speed * engine.time.deltaTime * engine.activeScene->activeCamera->transform->Right();
            if (engine.input.IsKeyHeld(KEY_RIGHT))
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
            engine.activeScene->activeCamera->transform->rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
        }

        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        sceneViewActive = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
        // ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        windowPos = vMin;

        ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

        if (engine.window.GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
        {
            if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
            {
                engine.window.SetWindowSize({windowSize.x, windowSize.y});
                engine.renderer.SetViewport({windowSize.x, windowSize.y});
            }
        }

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(uintptr_t)engine.renderer.renderTexture,
            vMin,
            vMax,
            ImVec2(0, 1),
            ImVec2(1, 0));

        if (selectedEntity != entt::null && engine.activeScene->Has<Transform>(selectedEntity) && engine.activeScene->activeCamera != nullptr)
        {
            Transform &transform = engine.activeScene->Get<Transform>(selectedEntity);

            glm::mat4 model = transform.GetModelMatrix();

            ImGuizmo::SetOrthographic(engine.activeScene->activeCamera->isOrtho);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, engine.window.GetWindowSize().x, engine.window.GetWindowSize().y);

            float snap = 1.f;
            if (gizmoOperation == ImGuizmo::OPERATION::ROTATE)
                snap = 45.f;

            ImGuizmo::Manipulate(glm::value_ptr(engine.activeScene->activeCamera->view), glm::value_ptr(engine.activeScene->activeCamera->projection), gizmoOperation, currentGizmoMode, glm::value_ptr(model), NULL, engine.input.IsKeyHeld(KEY_LEFT_SHIFT) ? &snap : NULL);

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
        const float padding = 10.f;
        const float iconSize = 25.f;

        ImGui::SetNextWindowPos(ImVec2(windowPos.x + padding, windowPos.y + padding));

        ImGuiWindowFlags windowFlags = 0 | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::Begin("Tool Bar", NULL, windowFlags);
        ImGui::PopStyleVar();

        ImGuizmo::OPERATION currentGizmoOperation = gizmoOperation;

        if (currentGizmoOperation == ImGuizmo::TRANSLATE)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(64.f / 255.f, 64.f / 255.f, 64.f / 255.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)translateIconId, ImVec2(iconSize, iconSize)))
            gizmoOperation = ImGuizmo::TRANSLATE;
        if (currentGizmoOperation == ImGuizmo::TRANSLATE)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        if (currentGizmoOperation == ImGuizmo::ROTATE)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(64.f / 255.f, 64.f / 255.f, 64.f / 255.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)rotateIconId, ImVec2(iconSize, iconSize)))
            gizmoOperation = ImGuizmo::ROTATE;
        if (currentGizmoOperation == ImGuizmo::ROTATE)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        if (currentGizmoOperation == ImGuizmo::SCALE)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(64.f / 255.f, 64.f / 255.f, 64.f / 255.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)scaleIconId, ImVec2(iconSize, iconSize)))
            gizmoOperation = ImGuizmo::SCALE;
        if (currentGizmoOperation == ImGuizmo::SCALE)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        ImGui::End();
    }
}
