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
            Invoke(Events::AssignPopup);
        if (selectedEntity != entt::null && ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
            Invoke(Events::RemovePopup);

        ImGui::End();
    }
}