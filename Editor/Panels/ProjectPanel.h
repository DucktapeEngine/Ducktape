#pragma once

#include <Panels/Panel.h>

namespace DT
{
    class ProjectPanel : public Panel
    {
    public:
        inline std::string GetWindowName() override { return "Project"; }

        void Update(ContextPtr &ctx) override;
    };
}