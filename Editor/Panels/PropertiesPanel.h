#pragma once

#include <Panels/Panel.h>
#include <Components/Camera.h>
#include <Components/Transform.h>
#include <Components/Tag.h>
#include <Components/DirectionalLight.h>
#include <Components/MeshRenderer.h>
#include <Components/PointLight.h>
#include <Scene/Entity.h>
#include <Panels/ComponentMenuPanel.h>
#include <Core/EventHandler.h>

namespace DT
{
	class PropertiesPanel : public Panel
	{
	public:
		Entity selectedEntity;

		inline std::string GetWindowName() override { return "Properties"; }

		void Update(Engine &engine) override;
	};
}