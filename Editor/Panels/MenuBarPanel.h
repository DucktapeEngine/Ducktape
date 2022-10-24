#pragma once

#include <Panels/Panel.h>
#include <Components/Camera.h>
#include <Components/Transform.h>
#include <Components/Tag.h>
#include <Components/DirectionalLight.h>
#include <Components/MeshRenderer.h>
#include <Components/PointLight.h>
#include <Scene/Entity.h>

namespace DT
{
    class MenuBarPanel : public Panel
    {
    public:
        void Update(Engine &engine) override;
    };
}