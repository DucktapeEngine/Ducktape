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

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <json/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <entt/entt.hpp>

#include <Core/Entity.h>

using json = nlohmann::json;

#define COMPONENT(componentName) engine->inspector.Component(componentName, this->entity);
#define PROPERTY(property, valuePtr) engine->inspector.Property(property, valuePtr);

namespace DT
{
    void Inspect(const std::string &label, float *value);
    void Inspect(const std::string &label, glm::vec3 *value);
    void Inspect(const std::string &label, bool *value);
    void Inspect(const std::string &label, glm::quat *value);
    void Inspect(const std::string &label, std::string *value);

    class Inspector
    {
    public:
        std::string lastComponentName;
        bool lastComponentHeaderOpen = false;

        void Component(const std::string &componentName, Entity entityHandle);

        template <typename T>
        void Property(const std::string &label, T *value)
        {
            if(lastComponentHeaderOpen)
                Inspect(label + "##" + lastComponentName, value);
        }
    };
}