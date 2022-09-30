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

#include <imgui.h>
#include <ImGuizmo.h>

#include <Renderer/Renderer.h>
#include <Renderer/ModelLoader.h>
#include <Renderer/Mesh.h>
#include <Input/Input.h>
#include <Core/Time.h>
#include <Core/Engine.h>
#include <Components/Tag.h>
#include <Core/Debug.h>

#define DEG2RAD 0.0174533f

namespace DT
{
    namespace EditorModules
    {
        void Init(Engine *engine);

        inline float snap;
        inline bool useSnap = false;
        inline ImGuizmo::OPERATION currentGizmoOperation(ImGuizmo::ROTATE);
        inline ImGuizmo::MODE currentGizmoMode(ImGuizmo::WORLD);
        void ToolBar(Engine *engine, const ImVec2 &windowPos, const ImVec2 &windowSize);

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