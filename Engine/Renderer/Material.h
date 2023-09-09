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
#include <Renderer/Texture.h>
#include <Renderer/Shader.h>
#include <Core/Resource.h>
#include <Core/ContextPtr.h>

namespace DT
{
    struct Material
    {
        glm::vec3 diffuseColor = glm::vec3(1.0f);
        glm::vec3 specularColor = glm::vec3(1.0f);
        glm::vec3 ambientColor = glm::vec3(1.0f);
        float shininess = 0.5f;
        Resource<Texture> texture;
        Texture::Type textureType = Texture::Type::DIFFUSE;
        Resource<Shader> shader;

        static inline std::unordered_map<RID, Material *> factoryData;

        static Material *LoadResource(RID rid, ContextPtr &ctx)
        {
            if (factoryData.count(rid))
                return factoryData[rid];

            JLOG();
            factoryData[rid] = new Material(json::parse(std::ifstream(ctx.resourceManager->GetPath(rid))));
            return factoryData[rid];
        }

        static void UnLoadResource(RID rid)
        {
            delete factoryData[rid];
            factoryData.erase(rid);
        }

        static void SaveResource(RID rid, ContextPtr &ctx)
        {
            std::ofstream out(ctx.resourceManager->GetPath(rid));
            json j = *factoryData[rid];
            out << j;
        }

        IN_SERIALIZE(Material, diffuseColor, specularColor, ambientColor, shininess, texture, textureType, shader);
    };
}