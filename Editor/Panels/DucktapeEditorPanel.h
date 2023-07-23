#pragma once

#include <Panels/Panel.h>
#include <Core/Serialization.h>

namespace DT
{
    class DucktapeEditorPanel : public Panel
    {
    public:
        inline std::string GetWindowName() override { return "Ducktape Editor " + std::to_string(DUCKTAPE_VERSION_MAJOR) + "." + std::to_string(DUCKTAPE_VERSION_MINOR) + "." + std::to_string(DUCKTAPE_VERSION_PATCH); }

        void Start(ContextPtr &ctx) override
        {
            isOpen = true;
        }

        void Update(ContextPtr &ctx) override
        {
            ImGui::Begin(GetWindowName().c_str(), &isOpen);

            ImGui::TextUnformatted("Welcome to Ducktape.");

            ImGui::End();
        }
    };
}