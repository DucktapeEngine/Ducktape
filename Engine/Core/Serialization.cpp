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

#include <Core/Serialization.h>

namespace DT
{
    void Serialization::Component(const std::string &componentName, Entity entity)
    {
        lastComponentName = componentName;

        lastComponentHeaderOpen = ImGui::CollapsingHeader(componentName.c_str());

        if (isDump)
        {
            dump["components"].push_back({});
            dumpComponentIdx++;
            dump["components"][dumpComponentIdx]["id"] = componentName;
            dump["components"][dumpComponentIdx]["entity"] = entity.handle;
        }
    }

    json Serialize(const std::string &label, float *value)
    {
        ImGui::InputFloat(label.c_str(), value);
        return json(*value);
    }

    json Serialize(const std::string &label, glm::vec3 *value)
    {
        ImGui::InputFloat3(label.c_str(), &value->x);
        json j;
        j["x"] = value->x;
        j["y"] = value->y;
        j["z"] = value->z;
        return j;
    }

    json Serialize(const std::string &label, bool *value)
    {
        ImGui::Checkbox(label.c_str(), value);
        return json(*value);
    }

    json Serialize(const std::string &label, glm::quat *value)
    {
        ImGui::InputFloat4(label.c_str(), &value->x);
        json j;
        j["x"] = value->x;
        j["y"] = value->y;
        j["z"] = value->z;
        j["w"] = value->w;
        return j;
    }

    json Serialize(const std::string &label, std::string *value)
    {
        ImGui::InputText(label.c_str(), value);
        return json(*value);
    }
}