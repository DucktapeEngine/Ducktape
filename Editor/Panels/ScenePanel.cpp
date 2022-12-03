#include <Panels/ScenePanel.h>

namespace DT
{
    const char *ScenePanel::GetWindowName() { return windowName; }

    void ScenePanel::Update(Engine &engine)
    {
        ImGui::Begin(windowName, &isOpen);

        if (ImGui::Button("Save", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
        {
            SceneManager::Save(engine.project.directory / "Resources" / "Scenes" / "MainScene.json", *engine.activeScene, engine);
        }

        if (ImGui::Button("Load", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
        {
            SceneManager::Load(engine.project.directory / "Resources" / "Scenes" / "MainScene.json", *engine.activeScene, engine);
            selectedEntity = entt::null;
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
                } });
        ImGui::End();
    }
}