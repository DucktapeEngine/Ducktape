#pragma once

#include <Panels/Panel.h>
#include <Panels/PropertiesPanel.h>
#include <Editor.h>

namespace DT
{
    class RemoveComponentMenuPanel : public Panel
    {
    public:
        inline std::string GetWindowName() override { return "Remove Component Menu"; }
        std::string removeComponentInput;

        PropertiesPanel *propertiesPanel;

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
    };
}