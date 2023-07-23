#include <Panels/ComponentMenuPanel.h>

namespace DT
{
    void ComponentMenuPanel::Open()
    {
        isOpen = true;
    }

    void ComponentMenuPanel::Update(ContextPtr &ctx)
    {
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        static const std::array<std::string, 7> builtinComponentList = {"Camera", "DirectionalLight", "MeshRenderer", "PointLight", "Relation", "Tag", "Transform"};

        ImGui::InputTextWithHint("##componentName", "Component Name", &componentInput);
        ImGui::SameLine();
        if (ImGui::Button("Select"))
        {
            selectedComponent = componentInput;
            Invoke(Events::Selected);
            isOpen = false;
        }

        for (const std::string component : builtinComponentList)
        {
            if (ImGui::Button((component + "##componentMenu").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 20.f)))
            {
                selectedComponent = component;
                Invoke(Events::Selected);
                isOpen = false;
            }
        }

        ImGui::End();
    }
}