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

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <nlohmann/json.hpp>

#define serialize NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
#define IN_SERIALIZE NLOHMANN_DEFINE_TYPE_INTRUSIVE

#define JSON_DEBUG

// #ifdef debug // todo: add debug flag with support for cmake // i'll be honest i've no idea what this todo is supposed to mean
#ifdef JSON_DEBUG
#define jlog() std::cout << "[jlog] " << __FILE__ << ":" << __LINE__ << "\n";
#endif
#ifndef JSON_DEBUG
#define jlog() ;
#endif

namespace glm {
serialize(vec2, x, y);
serialize(vec3, x, y, z);
serialize(quat, x, y, z, w);
} // namespace glm