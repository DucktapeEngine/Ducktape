#pragma once

#include <Panels/Panel.h>
#include <Scene/SceneManager.h>
#include <Scene/Entity.h>
#include <Components/Tag.h>
#include <Components/Relation.h>

namespace DT
{
	class ScenePanel : public Panel
	{
	public:
		inline std::string GetWindowName() override { return "Scene"; }

		void DrawSelectibleEntity(Entity entity, Engine &engine);
		void Update(Engine &engine) override;

		Entity selectedEntity;
	};
}