#pragma once

#include <Panels/Panel.h>
#include <Core/Macro.h>

namespace DT
{
    class DucktapeEditorPanel : public Panel
    {
    public:
        inline std::string GetWindowName() override { return "Ducktape Editor " + std::to_string(DUCKTAPE_VERSION_MAJOR) + "." + std::to_string(DUCKTAPE_VERSION_MINOR) + "." + std::to_string(DUCKTAPE_VERSION_PATCH); }

        void Start(Engine &engine) override
        {
            isOpen = true;
        }

        void Update(Engine &engine) override
        {
            ImGui::Begin(GetWindowName().c_str(), &isOpen);

            ImGui::TextUnformatted("Welcome to Ducktape.");

            ImGui::End();
        }
    };
}