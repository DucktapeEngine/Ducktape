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

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace DT
{
    /**
     * @brief Configurator class for GLFW window and Ducktape engine properties
     */
    class Configuration
    {
    public:
        glm::vec2 windowSize;                           ///< @brief GLFW window size
        std::string windowTitle;                        ///< @brief GLFW window title
        glm::vec3 version;                              ///< @brief GLFW application version
        std::string windowIconPath;                     ///< @brief Path to GLFW window icon
        int targetFPS;                                  ///< @brief Engine target FPS
        bool drawWireframe = false;                     ///< @brief Flag for wireframe draw mode
        bool vsync = true;                              ///< @brief Flag for VSYNC setting
        GLFWwindow *shareContextWith = nullptr;         ///< @brief GLFW window context to share with OpenGL
        bool hideWindow = false;                        ///< @brief Flag for window hiding
        bool drawToQuad = true;                         ///< @brief Flag for quad drawing
        std::array<std::string, 6> skyboxCubemapPaths;  ///< @brief Path list for all 6 cubemap faces
    };
}