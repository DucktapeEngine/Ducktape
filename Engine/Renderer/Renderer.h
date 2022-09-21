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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Core/Configuration.h>
#include <Renderer/Camera.h>
#include <Core/Window.h>
#include <Core/Debug.h>
#include <Renderer/Cubemap.h>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace DT
{
    class Renderer
    {
    public:
        unsigned int FBO, RBO, renderTexture;
        unsigned int quadVAO, quadVBO;
        unsigned int skyboxVAO, skyboxVBO;
        Cubemap skyboxCubemap;
        Shader defaultShader, screenShader, skyboxShader;

        glm::vec3 lightColor = {1.f, 1.f, 1.f}, lightPos = {0.f, 0.f, 0.f};

        void Init(Window &window, Configuration &config);
        void Render(Camera &camera, Window &window, Configuration &config);
        void Terminate();

        void LoadSkybox(std::array<std::string, 6> paths);
    };
}