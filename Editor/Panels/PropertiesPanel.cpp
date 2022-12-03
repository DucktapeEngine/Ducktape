#include <Panels/PropertiesPanel.h>

namespace DT
{
    const char *InspectorPanel::GetWindowName() { return windowName; }

    void InspectorPanel::RenderAddComponentMenu(Engine &engine)
    {
        // Add Component Menu
        static const std::array<std::string, 6> builtinComponentList = {"Camera", "DirectionalLight", "MeshRenderer", "PointLight", "Tag", "Transform"};

        if (openAddComponentMenu)
        {
            ImGui::InputTextWithHint("##addComponentName", "Component Name", &addComponentInput);
            ImGui::SameLine();
            if (ImGui::Button("+"))
            {
                engine.activeScene->Assign(selectedEntity, addComponentInput);
                openAddComponentMenu = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                openAddComponentMenu = false;
            }

            for (std::string component : builtinComponentList)
            {
                if (ImGui::Button((component + "##removeMenu").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
                {
                    if (component == "Camera")
                    {
                        engine.activeScene->Assign<Camera>(selectedEntity);
                    }
                    else if (component == "DirectionalLight")
                    {
                        engine.activeScene->Assign<DirectionalLight>(selectedEntity);
                    }
                    else if (component == "MeshRenderer")
                    {
                        engine.activeScene->Assign<MeshRenderer>(selectedEntity);
                    }
                    else if (component == "PointLight")
                    {
                        engine.activeScene->Assign<PointLight>(selectedEntity);
                    }
                    else if (component == "Tag")
                    {
                        engine.activeScene->Assign<Tag>(selectedEntity);
                    }
                    else if (component == "Transform")
                    {
                        engine.activeScene->Assign<Transform>(selectedEntity);
                    }
                    else
                    {
                        engine.activeScene->Assign(selectedEntity, component);
                    }
                    openAddComponentMenu = false;
                }
            }
        }

        if (!openAddComponentMenu)
            if (selectedEntity != entt::null && ImGui::Button("Assign", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
                openAddComponentMenu = true;
    }

    void PropertiesPanel::Update(Engine &engine)
    {
        selectedEntity = engine.activeScene->selectedEntity;

        ImGui::Begin(windowName, &isOpen);

        for (System *system : engine.activeScene->GetSystems())
            system->Inspector(engine.activeScene, engine.ctx);

        RenderAddComponentMenu(engine);

        ImGui::End();
    }
}