#pragma once

#include <Panels/Panel.h>

namespace DT
{
    class ProjectPanel : public Panel
    {
    public:
        void Update(Engine &engine) override;
    };
}