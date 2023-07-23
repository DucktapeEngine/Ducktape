#pragma once

#include <Panels/Panel.h>
#include <Core/EventHandler.h>
#include <Editor.h>

namespace DT
{
    class ComponentMenuPanel : public Panel, public EventHandler
    {
    public:
        inline std::string GetWindowName() override { return "Component Menu"; }
        std::string selectedComponent;

        enum Events
        {
            Selected,
        };

        void Open();

        void Update(ContextPtr &ctx) override;

    protected:
        std::string componentInput;
    };
}