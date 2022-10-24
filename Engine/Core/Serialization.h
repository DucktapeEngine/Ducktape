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

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <json/json.hpp>
using json = nlohmann::json;

#include <Scene/Entity.h>

#define SERIALIZE NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
#define IN_SERIALIZE NLOHMANN_DEFINE_TYPE_INTRUSIVE

namespace glm
{
    SERIALIZE(vec2, x, y);
    SERIALIZE(vec3, x, y, z);
    SERIALIZE(quat, x, y, z, w);
}

namespace DT
{
    class Serialization
    {
    public:
        json data;
        bool isSerializing = true;

        template <typename T>
        void SerializeComponent(const std::string componentName, T &component, Entity entity)
        {
            if (isSerializing)
            {
                json componentData = component;
                componentData["id"] = componentName;
                componentData["entity"] = entity;
                data["components"].push_back(componentData);
            }
            else
            {
                component = data["components"][0];
                data["components"].erase(data["components"].begin());
            }
        }
    };
}