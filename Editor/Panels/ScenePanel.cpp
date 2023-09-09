#include <Panels/ScenePanel.h>

namespace DT
{
    void ScenePanel::Update(ContextPtr &ctx)
    {
        if (ImGui::BeginPopupContextWindow())
        {
            ImGui::EndPopup();
        }

        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        ctx.sceneManager->GetActiveScene().registry.each([&](const Entity entity)
                                                         {
                                                   if (ctx.sceneManager->GetActiveScene().Has<Relation>(entity))
                                                   {
                                                       if (!ctx.sceneManager->GetActiveScene().Get<Relation>(entity)->hasParent)
                                                       {
                                                           DrawSelectibleEntity(entity, ctx);
                                                       }
                                                   }
                                                   else
                                                   {
                                                       DrawSelectibleEntity(entity, ctx);
                                                   } });

        ImGui::End();
    }

    void ScenePanel::DrawSelectibleEntity(Entity entity, ContextPtr &ctx)
    {
        std::string label = "Entity " + std::to_string(entt::to_integral(entity));

        if (ctx.sceneManager->GetActiveScene().Has<Tag>(entity))
        {
            std::string _label = ctx.sceneManager->GetActiveScene().registry.get<Tag>(entity).name;

            if (_label != "")
                label = _label;
        }

        if (ImGui::Selectable((label + "##" + std::to_string(entt::to_integral(entity))).c_str(), ctx.sceneManager->GetActiveScene().selectedEntity == entity))
        {
            ctx.sceneManager->GetActiveScene().selectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Create Entity"))
                ctx.sceneManager->GetActiveScene().CreateEntity();
            if (ImGui::MenuItem("Destroy Entity"))
                ctx.sceneManager->GetActiveScene().DestroyEntity(entity);
            ImGui::EndPopup();
        }

        if (ctx.sceneManager->GetActiveScene().Has<Relation>(entity))
        {
            Relation &relation = *ctx.sceneManager->GetActiveScene().Get<Relation>(entity);
            for (Entity child : relation.children)
            {
                ImGui::Indent();
                DrawSelectibleEntity(child, ctx);
                ImGui::Unindent();
            }
        }
    }
}