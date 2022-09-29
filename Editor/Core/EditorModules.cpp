/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSengine->  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Core/EditorModules.h>

namespace DT
{
    void EditorModules::Init(Engine *engine)
    {
    }

    void EditorModules::ToolBar(Engine *engine, const ImVec2 &windowPos, const ImVec2 &windowSize)
    {
        ImGui::Begin("Tool Bar");

        if (engine->input.GetKeyPressed(KEY_T))
            currentGizmoOperation = ImGuizmo::TRANSLATE;
        if (engine->input.GetKeyPressed(KEY_R))
            currentGizmoOperation = ImGuizmo::ROTATE;
        if (engine->input.GetKeyPressed(KEY_S))
            currentGizmoOperation = ImGuizmo::SCALE;
        if (ImGui::RadioButton("translate", currentGizmoOperation == ImGuizmo::TRANSLATE))
            currentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("rotate", currentGizmoOperation == ImGuizmo::ROTATE))
            currentGizmoOperation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("scale", currentGizmoOperation == ImGuizmo::SCALE))
            currentGizmoOperation = ImGuizmo::SCALE;

        if (currentGizmoOperation != ImGuizmo::SCALE)
        {
            if (ImGui::RadioButton("local", currentGizmoMode == ImGuizmo::LOCAL))
                currentGizmoMode = ImGuizmo::LOCAL;
            ImGui::SameLine();
            if (ImGui::RadioButton("world", currentGizmoMode == ImGuizmo::WORLD))
                currentGizmoMode = ImGuizmo::WORLD;
        }
        
        ImGui::Checkbox("snap", &useSnap);
        ImGui::SameLine();

        switch (currentGizmoOperation)
        {
        case ImGuizmo::TRANSLATE:
            ImGui::InputFloat3("Snap", &snap);
            break;
        case ImGuizmo::ROTATE:
            ImGui::InputFloat("Angle Snap", &snap);
            break;
        case ImGuizmo::SCALE:
            ImGui::InputFloat("Scale Snap", &snap);
            break;
        }

        ImGui::End();
    }

    void EditorModules::SceneView(Engine *engine)
    {
        //// Controls
        // Move
        const float speed = 2.5f, sensitivity = 25.f;

        if (engine->input.GetKey(KEY_UP))
            engine->camera.transform.position += speed * engine->time.deltaTime * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_DOWN))
            engine->camera.transform.position -= speed * engine->time.deltaTime * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_LEFT))
            engine->camera.transform.position += speed * engine->time.deltaTime * engine->camera.transform.Right();
        if (engine->input.GetKey(KEY_RIGHT))
            engine->camera.transform.position -= speed * engine->time.deltaTime * engine->camera.transform.Right();

        // Look
        if (engine->input.GetMouseButton(MOUSE_BUTTON_RIGHT))
        {
            yaw += -engine->input.mouseDelta.x * sensitivity * engine->time.deltaTime;
            pitch += engine->input.mouseDelta.y * sensitivity * engine->time.deltaTime;
            
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        engine->camera.transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
        
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin("Scene View");

        ImGui::Image((ImTextureID)(uintptr_t)engine->renderer.renderTexture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

        if (selectedEntity && selectedEntity.Has<Transform>())
        {
            Transform &transform = selectedEntity.Get<Transform>();

            glm::mat4 model = transform.GetModelMatrix();

            ImGuizmo::SetOrthographic(engine->camera.isOrtho);
            ImGuizmo::SetDrawlist();

            ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);
            ImGuizmo::Manipulate(glm::value_ptr(engine->camera.view), glm::value_ptr(engine->camera.projection), currentGizmoOperation, currentGizmoMode, glm::value_ptr(model), NULL, useSnap ? &snap : NULL);
            ImGuizmo::ViewManipulate(glm::value_ptr(engine->camera.view), glm::length(engine->camera.transform.position - transform.position), ImVec2(0, 0), ImVec2(128, 128), 0x10101010);

            transform.SetModelMatrix(model);
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ToolBar(engine, windowPos, windowSize);
    }

    void EditorModules::SceneViewLoop(Component *component)
    {
        component->SceneView(selectedEntity == component->entity);
    }

    void EditorModules::Hierarchy(Engine *engine)
    {
        ImGui::Begin("Hierarchy");

        engine->activeScene->sceneRegistry.each([&](const entt::entity entity)
                                               {
            std::string label = "Entity " + std::to_string(entt::to_integral(entity));

            if (engine->activeScene->sceneRegistry.any_of<Tag>(entity))
            {
                std::string _label = engine->activeScene->sceneRegistry.get<Tag>(entity).name;

                if (_label != "Unnamed")
                    label = _label;
            }

            if (ImGui::Selectable(label.c_str(), selectedEntity == entity))
            {
                selectedEntity = Entity(entity, engine->activeScene);
            } });

        ImGui::End();
    }

    void EditorModules::Console(Engine *engine)
    {
        ImGui::Begin("Console");

        ImGui::Text(engine->debug.log.c_str());

        ImGui::End();
    }

    void EditorModules::InspectorLoop(Component* component)
    {
        if (component->entity == selectedEntity)
        {
            component->Inspector();
            ImGui::Separator();
        }
    }

    void EditorModules::Inspector(Engine *engine)
    {
        ImGui::Begin("Inspector");

        engine->activeScene->CallLoop(InspectorLoop);

        ImGui::End();
    }
}