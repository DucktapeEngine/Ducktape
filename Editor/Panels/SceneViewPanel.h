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
		inline std::string GetWindowName() override { return "Scene View"; }

		void Start(ContextPtr &ctx) override;
		void Update(ContextPtr &ctx) override;

	protected:
		ImVec2 windowPos, windowSize;

		int translateIconId, rotateIconId, scaleIconId;
		int playIconId, pauseIconId, stopIconId;

		enum RuntimeState
		{
			Play,
			Pause,
			Stop
		};
		RuntimeState runtimeState = Stop;

		bool sceneViewActive = false;
		float yaw = 0.f, pitch = 0.f;
		Entity selectedEntity;
		ImGuizmo::OPERATION gizmoOperation = ImGuizmo::TRANSLATE;
		ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;

		void RenderToolbarPanel(ContextPtr &ctx);
	};
}