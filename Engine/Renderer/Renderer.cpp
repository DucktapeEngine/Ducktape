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
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
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
    void Renderer::Init(Window &window)
    {
        glEnable(GL_DEPTH_TEST);

        defaultShader.Load("../Resources/shaders/defaultV.glsl", "../Resources/shaders/defaultF.glsl");
        screenShader.Load("../Resources/shaders/screenV.glsl", "../Resources/shaders/screenF.glsl");

        // model.path = "../Resources/models/backpack/backpack.obj";
        // model.LoadModel(model.path);

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
    }

    void Renderer::Render(Camera &camera, Window &window, Configuration &config)
    {
        // Projection and View
        camera.view = glm::lookAt(camera.transform.position, camera.transform.position + camera.transform.Forward(), glm::vec3(0.0f, 1.0f, 0.0f));

        if (camera.isOrtho)
            camera.projection = glm::ortho(0.f, window.GetWindowSize().x, 0.f, window.GetWindowSize().y, 0.1f, 100.0f);
        else
            camera.projection = glm::perspective(glm::radians(camera.fov), window.GetWindowSize().x / window.GetWindowSize().y, 0.1f, 100.0f);

        defaultShader.Use();
        defaultShader.SetMat4("projection", camera.projection);
        defaultShader.SetMat4("view", camera.view);

        // glm::mat4 trans = glm::mat4(1.0f);
        // defaultShader.SetMat4("model", trans);

        // for (unsigned int i = 0; i < model.meshes.size(); i++)
        //     model.meshes[i].Draw(defaultShader);

        glCheckError();

        // Draw render texture on to a quad
        if (config.drawToQuad)
        {
            BindToFrameBuffer(false);
            glDisable(GL_DEPTH_TEST);

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            screenShader.Use();
            glBindVertexArray(quadVAO);
            glBindTexture(GL_TEXTURE_2D, renderTexture);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            BindToFrameBuffer(true);
            glEnable(GL_DEPTH_TEST);
        }
    }

    void Renderer::Terminate()
    {
        glDeleteFramebuffers(1, &FBO);
    }
    
    void Renderer::BindToFrameBuffer(bool bind)
    {
        if (bind)
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        else
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}