#include <Panels/ConsolePanel.h>

namespace DT
{
    void ConsolePanel::Update(Engine &engine)
    {
        ImGui::Begin("Console");

        ImGui::Text("%s", engine.debug.GetOut().c_str());
        ImGui::Text("%s", engine.debug.GetErr().c_str());

        ImGui::End();
    }
}