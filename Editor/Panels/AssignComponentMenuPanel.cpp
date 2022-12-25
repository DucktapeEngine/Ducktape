#include <Panels/AssignComponentMenuPanel.h>

namespace DT
{
    void AssignComponentMenuPanel::Start(Engine &engine)
    {
        propertiesPanel = Editor::GetPanel<PropertiesPanel>();
        propertiesPanel->OnEvent(PropertiesPanel::Events::AssignPopup, [&](EventHandler *event)
                                 { isOpen = true; });
    }

    void AssignComponentMenuPanel::Update(Engine &engine)
    {
        ImGuiWindow *propertyPanelWindow = ImGui::FindWindowByName("Properties");
        ImGui::SetNextWindowPos(propertyPanelWindow->Pos);
        ImGui::SetNextWindowSize(propertyPanelWindow->Size);

        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        static const std::array<std::string, 6> builtinComponentList = {"Camera", "DirectionalLight", "MeshRenderer", "PointLight", "Tag", "Transform"};

        ImGui::InputTextWithHint("##assignComponentName", "Component Name", &assignComponentInput);
        ImGui::SameLine();
        if (ImGui::Button("Assign"))
        {
            engine.activeScene->Assign(propertiesPanel->selectedEntity, assignComponentInput);
            isOpen = false;
        }

        for (std::string component : builtinComponentList)
        {
            if (ImGui::Button((component + "##addMenu").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
            {
                if (component == "Camera")
                    engine.activeScene->Assign<Camera>(propertiesPanel->selectedEntity);
                else if (component == "DirectionalLight")
                    engine.activeScene->Assign<DirectionalLight>(propertiesPanel->selectedEntity);
                else if (component == "MeshRenderer")
                    engine.activeScene->Assign<MeshRenderer>(propertiesPanel->selectedEntity);
                else if (component == "PointLight")
                    engine.activeScene->Assign<PointLight>(propertiesPanel->selectedEntity);
                else if (component == "Tag")
                    engine.activeScene->Assign<Tag>(propertiesPanel->selectedEntity);
                else if (component == "Transform")
                    engine.activeScene->Assign<Transform>(propertiesPanel->selectedEntity);
                isOpen = false;
            }
        }

        ImGui::End();
    }
}