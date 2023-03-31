#include <Panels/PropertiesPanel.h>

namespace DT
{
    void PropertiesPanel::Update(Engine &engine)
    {
        selectedEntity = engine.activeScene->selectedEntity;

        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        for (System *system : engine.activeScene->GetSystems())
            system->Inspector(engine.activeScene, engine.ctx);

        if (selectedEntity != entt::null && ImGui::Button("Assign", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { engine.activeScene->Assign(selectedEntity, componentMenuPanel->selectedComponent); });
        }

        if (selectedEntity != entt::null && ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
        {
            ComponentMenuPanel *componentMenuPanel = Editor::GetPanel<ComponentMenuPanel>();
            componentMenuPanel->Open();
            componentMenuPanel->OnEvent(ComponentMenuPanel::Events::Selected, [&](EventHandler *event)
                                        { engine.activeScene->Remove(selectedEntity, static_cast<ComponentMenuPanel *>(event)->selectedComponent); });
        }

        ImGui::End();
    }
}