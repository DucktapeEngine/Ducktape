#include <Panels/ConsolePanel.h>

namespace DT
{
    const char* ConsolePanel::GetWindowName() { return windowName; }

    void ConsolePanel::Update(Engine &engine)
    {
        ImGui::Begin(windowName);

        ImGui::TextWrapped("%s", engine.debug.GetOut().c_str());
        ImGui::TextWrapped("%s", engine.debug.GetErr().c_str());

        ImGui::End();
    }
}