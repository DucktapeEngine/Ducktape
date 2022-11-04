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
		const char* GetWindowName() override;
		const char* GetToolbarWindowName();

	private:
		const char* windowName = "Scene View";
		const char* toolbarWindowName = "Toolbar";
		void RenderToolbarPanel(Engine &engine);
		bool sceneViewActive = false;
		float yaw = 0.f, pitch = 0.f;
		Entity selectedEntity;
		ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
		ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;
	};
}