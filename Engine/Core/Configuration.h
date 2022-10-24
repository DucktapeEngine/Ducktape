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
#include <sstream>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Serialization.h>

namespace DT
{
    /**
     * @brief Configurator class for GLFW window and Ducktape engine properties
     */
    class Configuration
    {
    public:
        glm::vec2 windowSize = glm::vec2(500.f, 500.f); ///< @brief GLFW window size
        std::string windowTitle = "Untitled Ducktape Project";  ///< @brief GLFW window title
        glm::vec3 version = glm::vec3(1.f, 1.f, 1.f);   ///< @brief GLFW application version
        std::filesystem::path windowIconPath;                     ///< @brief Path to GLFW window icon
        int targetFPS = 60.f;                           ///< @brief Engine target FPS
        bool drawWireframe = false;                     ///< @brief Flag for wireframe draw mode
        bool vsync = true;                              ///< @brief Flag for VSYNC setting
        GLFWwindow *shareContextWith = nullptr;         ///< @brief GLFW window context to share with OpenGL
        bool hideWindow = false;                        ///< @brief Flag for window hiding
        bool drawToQuad = true;                         ///< @brief Flag for quad drawing
        std::array<std::filesystem::path, 6> skyboxCubemapPaths;  ///< @brief Path list for all 6 cubemap faces
        std::filesystem::path projectDirectory;
        std::filesystem::path gameModule;

        IN_SERIALIZE(Configuration, windowSize, windowTitle, version, windowIconPath, targetFPS, drawWireframe, vsync, hideWindow, drawToQuad, skyboxCubemapPaths);

        Configuration() = default;
        Configuration(std::filesystem::path configPath)
        {
            std::ifstream configFile((configPath / "DucktapeProjectSettings.json").string());
            std::stringstream buffer;
            buffer << configFile.rdbuf();
            from_json(json::parse(buffer.str()), *this);

            projectDirectory = configPath;
        }
    };
}