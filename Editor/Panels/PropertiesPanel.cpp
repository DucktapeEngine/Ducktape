#include <Panels/PropertiesPanel.h>

namespace DT
{
    void PropertiesPanel::Update(Engine &engine)
    {
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        for (System *system : engine.activeScene->systems)
            system->Inspector(engine.activeScene, engine.ctx);

        if (engine.activeScene->selectedEntity != entt::null && ImGui::Button("Assign", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { engine.activeScene->Assign(engine.activeScene->selectedEntity, static_cast<ComponentMenuPanel *>(event)->selectedComponent); });
        }

        if (engine.activeScene->selectedEntity != entt::null && ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { engine.activeScene->Remove(engine.activeScene->selectedEntity, static_cast<ComponentMenuPanel *>(event)->selectedComponent); });
        }

        ImGui::End();
    }
}