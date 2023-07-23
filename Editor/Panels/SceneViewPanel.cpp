#include <Panels/SceneViewPanel.h>

namespace DT
{
    void SceneViewPanel::Start(ContextPtr &ctx)
    {
        translateIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "translate.png"), ctx)->id;
        rotateIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "rotate.png"), ctx)->id;
        scaleIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "SceneView" / "scale.png"), ctx)->id;

        playIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "start.png"), ctx)->id;
        pauseIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "pause.png"), ctx)->id;
        stopIconId = Texture::LoadResource(ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Icons" / "MenuBar" / "stop.png"), ctx)->id;

        ctx.input->OnKeyEvent([&](Key key, Action action)
                              {
                                    if (key == KEY_T && action == PRESS)
                                        gizmoOperation = ImGuizmo::TRANSLATE;
                                    if (key == KEY_R && action == PRESS)
                                        gizmoOperation = ImGuizmo::ROTATE;
                                    if (key == KEY_S && action == PRESS)
                                        gizmoOperation = ImGuizmo::SCALE; });
    }

    void SceneViewPanel::Update(ContextPtr &ctx)
    {
        selectedEntity = ctx.sceneManager->GetActiveScene().selectedEntity;
        if (sceneViewActive && ctx.sceneManager->GetActiveScene().activeCamera != nullptr)
        {
            // Controls
            // Move
            const float speed = 2.5f, sensitivity = 25.f;
            bool holdingRightButton = ctx.input->IsMouseButtonHeld(MOUSE_BUTTON_RIGHT);

            if (ctx.input->IsKeyHeld(KEY_UP))
                ctx.sceneManager->GetActiveScene().activeCamera->transform->translation += speed * ctx.time->deltaTime * ctx.sceneManager->GetActiveScene().activeCamera->transform->Forward();
            if (ctx.input->IsKeyHeld(KEY_DOWN))
                ctx.sceneManager->GetActiveScene().activeCamera->transform->translation -= speed * ctx.time->deltaTime * ctx.sceneManager->GetActiveScene().activeCamera->transform->Forward();
            if (ctx.input->IsKeyHeld(KEY_LEFT))
                ctx.sceneManager->GetActiveScene().activeCamera->transform->translation += speed * ctx.time->deltaTime * ctx.sceneManager->GetActiveScene().activeCamera->transform->Right();
            if (ctx.input->IsKeyHeld(KEY_RIGHT))
                ctx.sceneManager->GetActiveScene().activeCamera->transform->translation -= speed * ctx.time->deltaTime * ctx.sceneManager->GetActiveScene().activeCamera->transform->Right();

            // Look
            if (holdingRightButton)
            {
                yaw += -ctx.input->mouseDelta.x * sensitivity * ctx.time->deltaTime;
                pitch += ctx.input->mouseDelta.y * sensitivity * ctx.time->deltaTime;

                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }
            ctx.sceneManager->GetActiveScene().activeCamera->transform->rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
        }

        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        sceneViewActive = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        windowPos = vMin;

        ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

        if (ctx.window->GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
        {
            if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
            {
                ctx.window->SetWindowSize({windowSize.x, windowSize.y});
                ctx.renderer->SetViewport({windowSize.x, windowSize.y});
            }
        }

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(uintptr_t)ctx.renderer->renderTexture,
            vMin,
            vMax,
            ImVec2(0, 1),
            ImVec2(1, 0));

        if (selectedEntity != entt::null && ctx.sceneManager->GetActiveScene().Has<Transform>(selectedEntity) && ctx.sceneManager->GetActiveScene().activeCamera != nullptr)
        {
            Transform *transform = ctx.sceneManager->GetActiveScene().Get<Transform>(selectedEntity);

            glm::mat4 model = transform->GetModelMatrix();

            ImGuizmo::SetOrthographic(ctx.sceneManager->GetActiveScene().activeCamera->isOrtho);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, ctx.window->GetWindowSize().x, ctx.window->GetWindowSize().y);

            float snap = 1.f;
            if (gizmoOperation == ImGuizmo::OPERATION::ROTATE)
                snap = 45.f;

            ImGuizmo::Manipulate(glm::value_ptr(ctx.sceneManager->GetActiveScene().activeCamera->view), glm::value_ptr(ctx.sceneManager->GetActiveScene().activeCamera->projection), gizmoOperation, currentGizmoMode, glm::value_ptr(model), NULL, ctx.input->IsKeyHeld(KEY_LEFT_SHIFT) ? &snap : NULL);

            if (ImGuizmo::IsUsing())
            {
                transform->SetModelMatrix(model);
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        RenderToolbarPanel(ctx);
    }

    void SceneViewPanel::RenderToolbarPanel(ContextPtr &ctx)
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
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
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
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
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

        // Runtime state control
        RuntimeState currentRuntimeState = runtimeState;

        if (currentRuntimeState == RuntimeState::Play)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)playIconId, ImVec2(iconSize, iconSize)))
        {
            runtimeState = RuntimeState::Play;
            ctx.loopManager->gameTick = true;
        }
        if (currentRuntimeState == RuntimeState::Play)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        if (currentRuntimeState == RuntimeState::Pause)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)pauseIconId, ImVec2(iconSize, iconSize)))
        {
            runtimeState = RuntimeState::Pause;
            ctx.loopManager->gameTick = false;
        }
        if (currentRuntimeState == RuntimeState::Pause)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        if (currentRuntimeState == RuntimeState::Stop)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        }
        if (ImGui::ImageButton((ImTextureID)(uintptr_t)stopIconId, ImVec2(iconSize, iconSize)))
        {
            runtimeState = RuntimeState::Stop;
            ctx.loopManager->gameTick = false;
            ctx.loopManager->sceneTick = true;
        }
        if (currentRuntimeState == RuntimeState::Stop)
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }

        ImGui::End();
    }
}
