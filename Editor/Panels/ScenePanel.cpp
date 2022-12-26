#include <Panels/ScenePanel.h>

namespace DT
{
    void ScenePanel::Update(Engine &engine)
    {
        if (ImGui::BeginPopupContextWindow())
        {
            ImGui::EndPopup();
        }

        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        if (ImGui::Button("Save", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
        {
            SceneManager::Save(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "Scenes" / "MainScene.json", *engine.activeScene, engine);
        }

        if (ImGui::Button("Load", ImVec2(ImGui::GetWindowContentRegionWidth(), 20.f)))
        {
            SceneManager::Load(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "Scenes" / "MainScene.json", *engine.activeScene, engine);
            selectedEntity = entt::null;
        }

        engine.activeScene->sceneRegistry.each([&](const Entity entity)
                                               {
            std::string label = "Entity " + std::to_string(entt::to_integral(entity));

            if (engine.activeScene->Has<Tag>(entity))
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

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Create Entity"))
                    engine.activeScene->CreateEntity();
                if (ImGui::MenuItem("Destroy Entity"))
                    engine.activeScene->DestroyEntity(entity);
                ImGui::EndPopup();
            } });

        ImGui::End();
    }
}