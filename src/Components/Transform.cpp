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

#include <Components/Transform.h>

namespace DT
{
    void Transform::SetEulerAngles(const glm::vec3 &eulerAngles)
    {
        rotation.x = cos(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.y));
        rotation.y = sin(glm::radians(eulerAngles.y));
        rotation.z = sin(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.y));
        rotation = glm::normalize(rotation);
    }

    void Transform::OnGUI()
    {
        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Text("Position");
            ImGui::SameLine();
            ImGui::InputFloat3("##Position", &position[0]);

            ImGui::Text("Rotation");
            ImGui::SameLine();
            ImGui::InputFloat3("##Rotation", &rotation[0]);

            ImGui::Text("Scale");
            ImGui::SameLine();
            ImGui::InputFloat3("##Scale", &scale[0]);

            EndGUI();
        }
    }
}