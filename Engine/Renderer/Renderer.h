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

#define MAX_LIGHT_NO 25

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Core/Configuration.h>
#include <Core/Window.h>
#include <Core/Debug.h>
#include <Renderer/Cubemap.h>
#include <Core/UserPointer.h>

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
        Shader defaultShader = Shader("../Resources/shaders/default.vert", "../Resources/shaders/default.frag");
        Shader screenShader = Shader("../Resources/shaders/screen.vert", "../Resources/shaders/screen.frag");
        Shader skyboxShader = Shader("../Resources/shaders/skybox.vert", "../Resources/shaders/skybox.frag");
        glm::vec2 customViewportSize;

        glm::mat4 *cameraView;
        glm::mat4 *cameraProjection;
        glm::vec3 *cameraPosition;
        glm::quat *cameraRotation;
        bool *isOrtho;
        float *fov;

        std::array<bool, MAX_LIGHT_NO> occupiedDirectionalLights = {false};
        std::array<bool, MAX_LIGHT_NO> occupiedPointLight = {false};

        Renderer(Window &window, Configuration &config);
        void Render(Window &window, Configuration &config);
        ~Renderer();

        void SetViewport(glm::vec2 viewportsize);

        void LoadSkybox(std::array<std::string, 6> paths);

        bool GetFreeDirectionalLightSpot(unsigned int *spot);
        void UnoccupyDirectionalLightSpot(unsigned int spot);
        bool GetFreePointLightSpot(unsigned int *spot);
        void UnoccupyPointLightSpot(unsigned int spot);
        
        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    };
}