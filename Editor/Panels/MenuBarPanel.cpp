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
                    engine.config.Save();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}