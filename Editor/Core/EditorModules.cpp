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

        ImGui::End();
    }

    void EditorModules::SceneView(Engine *engine)
    {
        //// Controls
        // Move
        const float speed = 2.5f, sensitivity = 25.f;

        if (engine->input.GetKey(KEY_UP))
            engine->activeScene->mainCamera->transform->position += speed * engine->time.deltaTime * engine->activeScene->mainCamera->transform->Forward();
        if (engine->input.GetKey(KEY_DOWN))
            engine->activeScene->mainCamera->transform->position -= speed * engine->time.deltaTime * engine->activeScene->mainCamera->transform->Forward();
        if (engine->input.GetKey(KEY_LEFT))
            engine->activeScene->mainCamera->transform->position += speed * engine->time.deltaTime * engine->activeScene->mainCamera->transform->Right();
        if (engine->input.GetKey(KEY_RIGHT))
            engine->activeScene->mainCamera->transform->position -= speed * engine->time.deltaTime * engine->activeScene->mainCamera->transform->Right();

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

        engine->activeScene->mainCamera->transform->rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
        
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin("Scene View");

        ImGui::Image((ImTextureID)(uintptr_t)engine->renderer.renderTexture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

        if (selectedEntity && selectedEntity.Has<Transform>())
        {
            Transform &transform = selectedEntity.Get<Transform>();

            // Removed ImGuizmo, add custom implementation here.
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

        if (ImGui::Button("Serialize"))
        {
            engine->serializer.isDump = true;
            engine->activeScene->CallLoop(InspectorLoop);
            engine->serializer.isDump = false;
            std::cout << engine->serializer.dump.dump(4) << std::endl;
        }

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
        if (component->engine->serializer.isDump || component->entity == selectedEntity)
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