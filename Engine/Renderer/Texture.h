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
#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/stb_image.h>

#include <Core/Serialization.h>
#include <Core/ResourceManager.h>

namespace DT
{
    /**
     * @brief Texture class for loading and using texture or image.
     */
    class Texture
    {
    public:
        int width;  ///< @brief Width of the image/texture.
        int height; ///< @brief Height of the image/texture.
        int nrChannels;
        unsigned int id;     ///< @brief Unique id of the texture.
        bool loaded = false; ///< @brief Whether the texture is loaded or not.

        enum Type
        {
            DIFFUSE,
            SPECULAR,
            NORMAL,
            HEIGHT
        };

        static inline std::unordered_map<RID, Texture *> factoryData;

        Texture() = default;

        /**
         * @brief Create a new Texture class
         * @param _path path to the texture/image to be loaded
         * @param _type type flag for the texture
         */
        Texture(RID rid);

        static Texture *LoadResource(RID rid)
        {
            if (factoryData.count(rid))
                return factoryData[rid];

            factoryData[rid] = new Texture(rid);
            return factoryData[rid];
        }

        static void UnLoadResource(RID rid)
        {
            delete factoryData[rid];
            factoryData.erase(rid);
        }

        /**
         * @brief  deletes the texture
         */
        void Delete();
    };
}