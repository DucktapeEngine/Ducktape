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

#include <Core/Inspector.h>

namespace DT
{
    void Inspector::Component(const std::string &componentName, Entity entity)
    {
        lastComponentName = componentName;
        lastComponentHeaderOpen = ImGui::CollapsingHeader(componentName.c_str());
    }

    void Inspect(const std::string &label, float *value)
    {
        ImGui::InputFloat(label.c_str(), value);
    }

    void Inspect(const std::string &label, glm::vec3 *value)
    {
        ImGui::InputFloat3(label.c_str(), &value->x);
    }

    void Inspect(const std::string &label, bool *value)
    {
        ImGui::Checkbox(label.c_str(), value);
    }

    void Inspect(const std::string &label, glm::quat *value)
    {
        ImGui::InputFloat4(label.c_str(), &value->x);
    }

    void Inspect(const std::string &label, std::string *value)
    {
        ImGui::InputText(label.c_str(), value);
    }
}