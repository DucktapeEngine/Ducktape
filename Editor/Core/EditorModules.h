/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <string>

#include <imgui.h>
#include <ImGuizmo.h>

#include <Components/Camera.h>
#include <Components/Transform.h>
#include <Components/Tag.h>
#include <Components/DirectionalLight.h>
#include <Components/MeshRenderer.h>
#include <Components/PointLight.h>
#include <Renderer/Renderer.h>
#include <Renderer/ModelLoader.h>
#include <Renderer/Mesh.h>
#include <Input/Input.h>
#include <Core/Time.h>
#include <Core/Engine.h>
#include <Core/Debug.h>
#include <Core/Editor.h>
#include <Core/SceneManager.h>

#define DEG2RAD 0.0174533f

namespace DT
{
    namespace EditorModules
    {
        void Init(Engine *engine);

        void ToolBar(Engine *engine);

        inline ImGuizmo::OPERATION currentGizmoOperation(ImGuizmo::TRANSLATE);
        inline ImGuizmo::MODE currentGizmoMode(ImGuizmo::WORLD);
        void SceneView(Engine *engine);
        void SceneViewLoop(Component *component);

        inline float yaw = 0.f, pitch = 0.f;
        inline Entity selectedEntity;
        void Hierarchy(Engine *engine);

        void Console(Engine *engine);

        void Inspector(Engine *engine);
        void InspectorLoop(Component* component);
    }
}