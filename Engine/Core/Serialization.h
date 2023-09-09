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
#define JSON_DIAGNOSTICS 1
#include <json/json.hpp>
using json = nlohmann::json;

#define SERIALIZE NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
#define IN_SERIALIZE NLOHMANN_DEFINE_TYPE_INTRUSIVE

#define JSON_DEBUG

// #ifdef DEBUG // TODO: Add DEBUG flag with support for CMAKE
// TODO: Add LOG/ERR macros
#ifdef JSON_DEBUG
#define JLOG() std::cout << "[JLOG] " << __FILE__ << ":" << __LINE__ << "\n";
#endif
#ifndef JSON_DEBUG
#define JLOG() ;
#endif

namespace glm
{
    SERIALIZE(vec2, x, y);
    SERIALIZE(vec3, x, y, z);
    SERIALIZE(quat, x, y, z, w);
}