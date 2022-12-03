#pragma once

#include <Panels/Panel.h>
#include <Scene/SceneManager.h>
#include <Scene/Entity.h>
#include <Components/Tag.h>

namespace DT
{
	class ScenePanel : public Panel
	{
	public:
		void Update(Engine &engine) override;
		const char* GetWindowName() override;
	private:
		const char* windowName = "Hierarchy";
		Entity selectedEntity;
	};
}