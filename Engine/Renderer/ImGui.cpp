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

#include <Renderer/ImGui.h>

void ImGui::Mesh(const std::string &label, DT::Mesh *mesh)
{
    // TOFIX: Point to the correct Resource once Resource System has been implemented
}

void ImGui::Material(const std::string &label, DT::Material *material)
{
    ImGui::Indent();
    if (ImGui::CollapsingHeader(label.c_str()))
    {
        ImGui::ColorEdit3("color", &material->color.x);
        ImGui::DragFloat("shininess", &material->shininess);
    }
    ImGui::Unindent();
}

void ImGui::Vec3(const std::string &label, glm::vec3 *vec3)
{
    ImGui::DragFloat3(label.c_str(), &vec3->x);
}

void ImGui::Vec2(const std::string &label, glm::vec2 *vec2)
{
    ImGui::DragFloat2(label.c_str(), &vec2->x);
}