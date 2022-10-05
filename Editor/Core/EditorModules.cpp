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
    void Editor::Init(Engine *_engine)
    {
        engine = _engine;
        
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(engine->window.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style.GrabRounding = style.FrameRounding = 2.3f;

        EditorModules::Init(engine);
    }
    
    void Editor::Render()
    {
        ImGui::DockSpaceOverViewport();

        EditorModules::SceneView(engine);
        // EditorModules::ToolBar(engine); // Called from EditorModules::SceneView() itself
        EditorModules::Hierarchy(engine);
        EditorModules::Console(engine);
        EditorModules::Inspector(engine);
    }

    void EditorModules::Init(Engine *engine)
    {
    }

    void EditorModules::ToolBar(Engine *engine)
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

        // Transform
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin("Scene View");


        ImVec2 windowPos = ImGui::GetWindowPos();
        // ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        ImVec2 windowSize = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);

        if (engine->window.GetWindowSize() != glm::vec2(windowSize.x, windowSize.y))
        {
            if (glm::vec2(windowSize.x, windowSize.y) != glm::vec2(0.f, 0.f))
            {
                engine->window.SetWindowSize({windowSize.x, windowSize.y});
                engine->renderer.SetViewport({windowSize.x, windowSize.y});
            }
        }

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(uintptr_t)engine->renderer.renderTexture, 
            vMin, 
            vMax,
            ImVec2(0, 1), 
            ImVec2(1, 0));

        if (selectedEntity && selectedEntity.Has<Transform>())
        {
            Transform &transform = selectedEntity.Get<Transform>();

            // Removed ImGuizmo, add custom implementation here.
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ToolBar(engine);
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

        //Add Component Menu
        static bool openAddComponentMenu = false;
        static std::string addComponentInput;
        static const std::array<std::string, 6> builtinComponentList = {"Camera", "DirectionalLight", "MeshRenderer", "PointLight", "Tag", "Transform"};

        if (openAddComponentMenu)
        {
            ImGui::InputTextWithHint("##addComponentName", "Component Name", &addComponentInput);
            ImGui::SameLine();
            if (ImGui::Button("+"))
            {
                selectedEntity.Assign(addComponentInput);
                openAddComponentMenu = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                openAddComponentMenu = false;
            }

            for (std::string component : builtinComponentList)
            {
                if (ImGui::Button((component + "##removeMenu").c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
                {
                    if (component == "Camera")
                    {
                        selectedEntity.Assign<Camera>();
                    }
                    else if (component == "DirectionalLight")
                    {
                        selectedEntity.Assign<DirectionalLight>();
                    }
                    else if (component == "MeshRenderer")
                    {
                        selectedEntity.Assign<MeshRenderer>();
                    }
                    else if (component == "PointLight")
                    {
                        selectedEntity.Assign<PointLight>();
                    }
                    else if (component == "Tag")
                    {
                        selectedEntity.Assign<Tag>();
                    }
                    else if (component == "Transform")
                    {
                        selectedEntity.Assign<Transform>();
                    }
                    else
                    {
                        selectedEntity.Assign(component);
                    }
                    openAddComponentMenu = false;
                }
            }
        }

        if (!openAddComponentMenu)
            if (selectedEntity && ImGui::Button("Assign", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
                openAddComponentMenu = true;

        if (!selectedEntity)
            openAddComponentMenu = false;

        // Remove Component menu
        static bool openRemoveComponentMenu = false;
        static std::string removeComponentInput;

        if (openRemoveComponentMenu)
        {
            ImGui::InputTextWithHint("##RemoveComponentName", "Component Name", &removeComponentInput);
            ImGui::SameLine();
            if (ImGui::Button("x"))
            {
                selectedEntity.Assign(removeComponentInput);
                openRemoveComponentMenu = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                openRemoveComponentMenu = false;
            }

            for (std::string component : builtinComponentList)
            {
                if (ImGui::Button((component + "##removeMenu").c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
                {
                    if (component == "Camera")
                    {
                        selectedEntity.Remove<Camera>();
                    }
                    else if (component == "DirectionalLight")
                    {
                        selectedEntity.Remove<DirectionalLight>();
                    }
                    else if (component == "MeshRenderer")
                    {
                        selectedEntity.Remove<MeshRenderer>();
                    }
                    else if (component == "PointLight")
                    {
                        selectedEntity.Remove<PointLight>();
                    }
                    else if (component == "Tag")
                    {
                        selectedEntity.Remove<Tag>();
                    }
                    else if (component == "Transform")
                    {
                        selectedEntity.Remove<Transform>();
                    }
                    else
                    {
                        selectedEntity.Remove(component);
                    }
                    openRemoveComponentMenu = false;
                }
            }
        }

        if (!openRemoveComponentMenu)
            if (selectedEntity && ImGui::Button("Remove", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
                openRemoveComponentMenu = true;

        if (!selectedEntity)
            openRemoveComponentMenu = false;

        ImGui::End();
    }
}