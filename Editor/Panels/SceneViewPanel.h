#pragma once

#include <Panels/Panel.h>
#include <Core/ImGui.h>
#include <Components/Transform.h>
#include <Components/Camera.h>
#include <Scene/Entity.h>

namespace DT
{
	class SceneViewPanel : public Panel
	{
	public:
		void Update(Engine &engine) override;

	private:
		void RenderToolbarPanel(Engine &engine);
		bool sceneViewActive = false;
		float yaw = 0.f, pitch = 0.f;
		Entity selectedEntity;
		ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
		ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;
	};
}