#include <Panels/PropertiesPanel.h>

namespace DT
{
    void PropertiesPanel::Update(ContextPtr &ctx)
    {
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        for (System *system : ctx.sceneManager->GetActiveScene().systems)
            system->Inspector(ctx, ctx.sceneManager->GetActiveScene().selectedEntity);

        if (ctx.sceneManager->GetActiveScene().selectedEntity != entt::null && ImGui::Button("Assign", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { ctx.sceneManager->GetActiveScene().Assign(ctx.sceneManager->GetActiveScene().selectedEntity, static_cast<ComponentMenuPanel *>(event)->selectedComponent, ctx); });
        }

        if (ctx.sceneManager->GetActiveScene().selectedEntity != entt::null && ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { ctx.sceneManager->GetActiveScene().Remove(ctx.sceneManager->GetActiveScene().selectedEntity, static_cast<ComponentMenuPanel *>(event)->selectedComponent, ctx); });
        }

        ImGui::End();
    }
}