#include "HierarchyPanel.h"

void DT::HierarchyPanel::Update(Engine& engine)
{
    ImGui::Begin("Hierarchy");

    if (ImGui::Button("Save", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
    {
        SceneManager::Save("../Resources/Scenes/scene.json", *engine.activeScene, engine);
    }

    engine.activeScene->sceneRegistry.each([&](const Entity entity)
    {
            std::string label = "Entity " + std::to_string(entt::to_integral(entity));

            if (engine.activeScene->sceneRegistry.any_of<Tag>(entity))
            {
                std::string _label = engine.activeScene->sceneRegistry.get<Tag>(entity).name;

                if (_label != "Unnamed")
                    label = _label;
            }

            if (ImGui::Selectable(label.c_str(), selectedEntity == entity))
            {
                selectedEntity = entity;
                engine.activeScene->selectedEntity = selectedEntity;
            } 
    });
    ImGui::End();
}