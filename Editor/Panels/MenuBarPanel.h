#pragma once

#include <Panels/Panel.h>
#include <Editor.h>
#include <Panels/ConsolePanel.h>
#include <Panels/ScenePanel.h>
#include <Panels/PropertiesPanel.h>
#include <Panels/ProjectPanel.h>
#include <Panels/ResourceBrowserPanel.h>
#include <Panels/ResourceInspectorPanel.h>
#include <Panels/SceneViewPanel.h>
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
        int playIconId, pauseIconId, stopIconId;

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
        bool RequestDefaultLayout=false;
    };
}