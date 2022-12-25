#pragma once

#include <Panels/Panel.h>
#include <Panels/PropertiesPanel.h>
#include <Editor.h>

namespace DT
{
    class AssignComponentMenuPanel : public Panel
    {
    public:
        inline std::string GetWindowName() override { return "Assign Component Menu"; }
        std::string assignComponentInput;

        PropertiesPanel *propertiesPanel;

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
    };
}