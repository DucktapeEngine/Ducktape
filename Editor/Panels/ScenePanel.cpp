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

        engine.activeScene->sceneRegistry.each([&](const Entity entity)
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
        // std::cout << entt::to_integral(entity) << std::endl;

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
        }

        // std::cout << "i am " << engine.activeScene->Assign<Tag>(entity).name << ". my children are ";
        if (engine.activeScene->Has<Relation>(entity))
        {
            Relation &relation = *engine.activeScene->Get<Relation>(entity);
            for (Entity child : relation.children)
            {
                ImGui::Indent();
                // std::cout << engine.activeScene->Assign<Tag>(child).name << " ";
                DrawSelectibleEntity(child, engine);
                ImGui::Unindent();
            }
        }
        // std::cout << std::endl;
    }
}