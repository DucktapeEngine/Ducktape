#include <Panels/RemoveComponentMenuPanel.h>

namespace DT
{
    void RemoveComponentMenuPanel::Start(Engine &engine)
    {
        propertiesPanel = Editor::GetPanel<PropertiesPanel>();
        propertiesPanel->OnEvent(PropertiesPanel::Events::RemovePopup, [&](EventHandler *event)
                                 { isOpen = true; });
    }

    void RemoveComponentMenuPanel::Update(Engine &engine)
    {
        ImGuiWindow *propertyPanelWindow = ImGui::FindWindowByName("Properties");
        ImGui::SetNextWindowPos(propertyPanelWindow->Pos);
        ImGui::SetNextWindowSize(propertyPanelWindow->Size);

        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        static const std::array<std::string, 6> builtinComponentList = {"Camera", "DirectionalLight", "MeshRenderer", "PointLight", "Tag", "Transform"};

        ImGui::InputTextWithHint("##removeComponentName", "Component Name", &removeComponentInput);
        ImGui::SameLine();
        if (ImGui::Button("Remove"))
        {
            engine.activeScene->Remove(propertiesPanel->selectedEntity, removeComponentInput);
            isOpen = false;
        }

        for (std::string component : builtinComponentList)
        {
            if (ImGui::Button((component + "##addMenu").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
            {
                if (component == "Camera")
                    engine.activeScene->Remove<Camera>(propertiesPanel->selectedEntity);
                else if (component == "DirectionalLight")
                    engine.activeScene->Remove<DirectionalLight>(propertiesPanel->selectedEntity);
                else if (component == "MeshRenderer")
                    engine.activeScene->Remove<MeshRenderer>(propertiesPanel->selectedEntity);
                else if (component == "PointLight")
                    engine.activeScene->Remove<PointLight>(propertiesPanel->selectedEntity);
                else if (component == "Tag")
                    engine.activeScene->Remove<Tag>(propertiesPanel->selectedEntity);
                else if (component == "Transform")
                    engine.activeScene->Remove<Transform>(propertiesPanel->selectedEntity);
                isOpen = false;
            }
        }

        ImGui::End();
    }
}