#include "ConsolePanel.h"

void DT::ConsolePanel::Update(Engine &engine)
{
    ImGui::Begin("Console");

    ImGui::Text("%s", engine.debug.GetOut());
    ImGui::Text("%s", engine.debug.GetErr());

    ImGui::End();
}