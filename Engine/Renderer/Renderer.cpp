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

#include <Renderer/Renderer.h>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

namespace DT
{
    Renderer::Renderer(Window &window, Configuration &config) : skyboxCubemap(config.skyboxCubemapPaths)
    {
        glEnable(GL_DEPTH_TEST);

        glfwSetFramebufferSizeCallback(window.window, FramebufferSizeCallback);

        // FBO
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Texture
        glGenTextures(1, &renderTexture);
        glBindTexture(GL_TEXTURE_2D, renderTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.GetWindowSize().x, window.GetWindowSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

        // RBO
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.GetWindowSize().x, window.GetWindowSize().y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Framebuffer not complete!" << std::endl;
            return;
        }

        // Quad
        float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                                // positions   // texCoords
                                -1.0f, 1.0f, 0.0f, 1.0f,
                                -1.0f, -1.0f, 0.0f, 0.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,

                                -1.0f, 1.0f, 0.0f, 1.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,
                                1.0f, 1.0f, 1.0f, 1.0f};

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        // Skybox
        float skyboxVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }

    void Renderer::Render(Window &window, Configuration &config)
    {
        // Projection and View
        *cameraView = glm::lookAt(*cameraPosition, *cameraPosition + *cameraRotation * glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.0f, 1.0f, 0.0f));

        if (*isOrtho)
            *cameraProjection = glm::ortho(0.f, window.GetWindowSize().x, 0.f, window.GetWindowSize().y, 0.1f, 100.0f);
        else
            *cameraProjection = glm::perspective(glm::radians(*fov), window.GetWindowSize().x / window.GetWindowSize().y, 0.1f, 100.0f);

        defaultShader.Use();
        defaultShader.SetMat4("projection", *cameraProjection);
        defaultShader.SetMat4("view", *cameraView);
        defaultShader.SetVec3("viewPos", *cameraPosition);

        // Draw skybox
        glDepthMask(GL_FALSE);

        skyboxShader.Use();
        skyboxShader.SetMat4("projection", *cameraProjection);
        skyboxShader.SetMat4("view", glm::mat4(glm::mat3(*cameraView)));

        glBindVertexArray(skyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxCubemap.id);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDepthMask(GL_TRUE);

        glCheckError();

        // Draw render texture on to a quad
        if (config.drawToQuad)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glDisable(GL_DEPTH_TEST);

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            screenShader.Use();
            glBindVertexArray(quadVAO);
            glBindTexture(GL_TEXTURE_2D, renderTexture);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
            glEnable(GL_DEPTH_TEST);
        }
    }

    Renderer::~Renderer()
    {
        glDeleteFramebuffers(1, &FBO);
    }

    void Renderer::SetViewport(glm::vec2 viewportsize)
    {
        glBindTexture(GL_TEXTURE_2D, renderTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, viewportsize.x, viewportsize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, viewportsize.x, viewportsize.y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void Renderer::LoadSkybox(std::array<std::string, 6> paths)
    {
        skyboxCubemap = Cubemap(paths);
    }

    bool Renderer::GetFreeDirectionalLightSpot(unsigned int *spot)
    {
        for (int i = 0; i < MAX_LIGHT_NO; i++)
        {
            if (occupiedDirectionalLights[i] == false)
            {
                occupiedDirectionalLights[i] = true;
                *spot = i;
                return true;
            }
        }
        return false;
    }

    void Renderer::UnoccupyDirectionalLightSpot(unsigned int spot)
    {
        occupiedDirectionalLights[spot] = false;
    }

    bool Renderer::GetFreePointLightSpot(unsigned int *spot)
    {
        for (int i = 0; i < MAX_LIGHT_NO; i++)
        {
            if (occupiedPointLight[i] == false)
            {
                occupiedPointLight[i] = true;
                *spot = i;
                return true;
            }
        }
        return false;
    }

    void Renderer::UnoccupyPointLightSpot(unsigned int spot)
    {
        occupiedPointLight[spot] = false;
    }

    void Renderer::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height)
    {
        reinterpret_cast<UserPointer *>(glfwGetWindowUserPointer(glfwWindow))->window->SetWindowSize({width, height});
        reinterpret_cast<UserPointer *>(glfwGetWindowUserPointer(glfwWindow))->renderer->SetViewport({width, height});
    }
}