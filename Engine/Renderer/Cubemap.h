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
#include <array>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utils/stb_image.h>

namespace DT
{
    /**
     * @brief Cubemap class for managing cubemap
     */
    class Cubemap
    {
    public:
        unsigned int id;     ///< @brief Unique ID for each cubemap

        /**
         * @brief Creare a new Cubemap object.
         * @param paths list of 6 texture/image path for the each side of cubemap
         */
        Cubemap(std::array<std::string, 6> paths);

        /**
         * @brief Destroys a Cubemap object.
         */
        ~Cubemap();
    };
}