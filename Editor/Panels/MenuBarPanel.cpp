#include "MenuBarPanel.h"

namespace DT
{
    void MenuBarPanel::Update(Engine &engine)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save"))
                {
                    std::ofstream output((engine.config.projectDirectory / "DucktapeProjectSettings.json").string());
                    json j = engine.config;
                    output << j.dump(4);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Set Default Layout"))
                {
                    RequestDefaultLayout = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}