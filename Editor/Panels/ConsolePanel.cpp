#include "ConsolePanel.h"

void DT::ConsolePanel::Update(Engine &engine)
{
    ImGui::Begin("Console");

    ImGui::Text("%s", engine.debug.log.c_str());

    ImGui::End();
}