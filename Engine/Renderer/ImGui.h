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

#include <vector>
#include <string>

#include <imgui/imgui.h>
#include <glm/glm.hpp>

#include <Renderer/Mesh.h>
#include <Renderer/Material.h>

namespace ImGui
{
    void Mesh(const std::string &label, DT::Mesh *mesh);
    void Material(const std::string &label, DT::Material *material);
    void Vec3(const std::string &label, glm::vec3 *vec3);
    void Vec2(const std::string &label, glm::vec2 *vec2);
}