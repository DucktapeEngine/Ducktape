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

#define DEG2RAD 0.0174533f

// Ducktape includes
#include <Components/RegisterComponentSystems.h>
#include <Core/Configuration.h>
#include <Core/Debug.h>
#include <Core/Engine.h>
#include <Core/Macro.h>
#include <Core/Time.h>
#include <Core/UserPointer.h>
#include <Core/Window.h>
#include <Core/LoopManager.h>
#include <Input/Input.h>
#include <Input/Key.h>
#include <Renderer/Renderer.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <Renderer/Cubemap.h>
#include <Renderer/ModelLoader.h>
#include <Renderer/ImGui.h>
#include <Scene/SceneManager.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>
#include <Scene/System.h>
#include <Scene/GenericSystem.h>