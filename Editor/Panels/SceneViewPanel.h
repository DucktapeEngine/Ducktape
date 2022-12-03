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
		void Start(Engine &engine) override;
		void Update(Engine &engine) override;

	private:
		ImVec2 windowPos;

		int translateIconId, rotateIconId, scaleIconId;

		bool sceneViewActive = false;
		float yaw = 0.f, pitch = 0.f;
		Entity selectedEntity;
		ImGuizmo::OPERATION gizmoOperation = ImGuizmo::TRANSLATE;
		ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;

		void RenderToolbarPanel(Engine &engine);
	};
}