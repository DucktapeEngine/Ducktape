/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <scene/scene_manager.h>
#include <renderer/renderer.h>
#include <components/tag.h>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "[INVALID_ENUM]";
            break;
        case GL_INVALID_VALUE:
            error = "[INVALID_VALUE]";
            break;
        case GL_INVALID_OPERATION:
            error = "[INVALID_OPERATION]";
            break;
        case GL_OUT_OF_MEMORY:
            error = "[OUT_OF_MEMORY]";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "[INVALID_FRAMEBUFFER_OPERATION]";
            break;
        }
        std::cout << "" << error << " [" << file << "] [" << line << "]\n";
    }
    return errorCode;
}

namespace DT
{
    Renderer::Renderer(Context &ctx) : screenShader(Shader::Load(ctx.projectPath / "engine" / "shaders" / "screen.frag", ctx.projectPath / "engine" / "shaders" / "screen.vert").Fatal("Renderer::Renderer()"))
    {
        window = ctx.GetService<Window>();
        glfwSetFramebufferSizeCallback(window->GetRawWindowPointer(), FramebufferSizeCallback);

        // Quad
        float quadVertices[] = {
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

        std::cout << "Renderer Constructed\n";
    }

    void Renderer::BeginScene(BaseCamera *camera)
    {
        activeRenderCamera = camera;

        glBindFramebuffer(GL_FRAMEBUFFER, activeRenderCamera->FBO);
        glEnable(GL_DEPTH_TEST);

        glClearColor(activeRenderCamera->backgroundColor.r, activeRenderCamera->backgroundColor.g, activeRenderCamera->backgroundColor.b, activeRenderCamera->backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndScene()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);

        glClearColor(0.f, 1.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_RenderFrameBuffer)
        {
            screenShader.Use();
            glBindVertexArray(quadVAO);
            glBindTexture(GL_TEXTURE_2D, activeRenderCamera->renderTexture);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    void Renderer::SetViewport(const glm::vec2 &newViewportSize)
    {
        viewportSize = newViewportSize;

        for (BaseCamera *cam : BaseCamera::cameras)
            cam->SetViewportSize(viewportSize);
    }

    void Renderer::ActivateShader(Shader &shader)
    {
        shader.Use();
        shader.SetMat4("projection", activeRenderCamera->projection);
        shader.SetMat4("view", activeRenderCamera->view);
        shader.SetVec3("viewPos", activeRenderCamera->GetPosition());
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
            if (occupiedPointLights[i] == false)
            {
                occupiedPointLights[i] = true;
                *spot = i;
                return true;
            }
        }
        return false;
    }

    void Renderer::UnoccupyPointLightSpot(unsigned int spot)
    {
        occupiedPointLights[spot] = false;
    }

    void Renderer::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height)
    {
        reinterpret_cast<Context *>(glfwGetWindowUserPointer(glfwWindow))->GetService<Window>()->SetWindowSize({width, height}); // TODO
        reinterpret_cast<Context *>(glfwGetWindowUserPointer(glfwWindow))->GetService<Renderer>()->SetViewport({width, height});
    }
}