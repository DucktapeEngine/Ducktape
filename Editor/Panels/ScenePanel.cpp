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

        engine.activeScene->registry.each([&](const Entity entity)
                                          {
                                                   if (engine.activeScene->Has<Relation>(entity))
                                                   {
                                                       if (!engine.activeScene->Get<Relation>(entity)->hasParent)
                                                       {
                                                           DrawSelectibleEntity(entity, engine);
                                                       }
                                                   }
                                                   else
                                                   {
                                                       DrawSelectibleEntity(entity, engine);
                                                   } });

        ImGui::End();
    }

    void ScenePanel::DrawSelectibleEntity(Entity entity, Engine &engine)
    {
        std::string label = "Entity " + std::to_string(entt::to_integral(entity));

        if (engine.activeScene->Has<Tag>(entity))
        {
            std::string _label = engine.activeScene->registry.get<Tag>(entity).name;

            if (_label != "Unnamed" && _label != "")
                label = _label;
        }

        if (ImGui::Selectable((label + "##" + std::to_string(entt::to_integral(entity))).c_str(), engine.activeScene->selectedEntity == entity))
        {
            engine.activeScene->selectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Create Entity"))
                engine.activeScene->CreateEntity();
            if (ImGui::MenuItem("Destroy Entity"))
                engine.activeScene->DestroyEntity(entity);
            ImGui::EndPopup();
        }

        if (engine.activeScene->Has<Relation>(entity))
        {
            Relation &relation = *engine.activeScene->Get<Relation>(entity);
            for (Entity child : relation.children)
            {
                ImGui::Indent();
                DrawSelectibleEntity(child, engine);
                ImGui::Unindent();
            }
        }
    }
}