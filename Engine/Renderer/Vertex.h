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
#include <Core/Serialization.h>

#define MAX_BONE_INFLUENCE 4

namespace DT
{
    struct Vertex
    {
        glm::vec3 position;                  /// @brief position vector of the vertex 
        glm::vec3 normal;                    /// @brief normal vector corresponding to the vertex
        glm::vec2 texCoords;                 /// @brief texture coordinate vector corresponding to the vertex
        glm::vec3 tangent;                   /// @brief tangent vector corresponding to the vertex
        glm::vec3 bitangent;                 /// @brief bi-tangent vector corresponding to the vertex
        int boneIDs[MAX_BONE_INFLUENCE];     /// @brief list of bone IDs
        float weights[MAX_BONE_INFLUENCE];   /// @brief list of weights
    };
    
    SERIALIZE(Vertex, position, normal, texCoords, tangent, bitangent);
}