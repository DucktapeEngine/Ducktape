/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#include <ECS/SceneManager.h>
#include <Renderer/Renderer.h>
#include <Components/Tag.h>

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
        std::cout << "[ERR] " << error << " [" << file << "] [" << line << "]\n";
    }
    return errorCode;
}

namespace DT
{
    Renderer::Renderer(Context &ctx, const json &rendererData) : screenShader(Shader::Load(ctx.projectPath / "Engine" / "Shaders" / "Screen.frag", ctx.projectPath / "Engine" / "Shaders" / "Screen.vert").Fatal("Renderer::Renderer()"))
    {
        renderFrameBuffer = rendererData.value("renderFrameBuffer", true);
        window = ctx.GetService<Window>().Fatal("Renderer::Renderer()");

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

        std::cout << "[LOG] Renderer Constructed\n";
    }

    void Renderer::BeginScene(BaseCamera *camera)
    {
        activeRenderCamera = camera;

        BindFrameBuffer(activeRenderCamera->FBO);
        glEnable(GL_DEPTH_TEST);

        glClearColor(activeRenderCamera->backgroundColor.r, activeRenderCamera->backgroundColor.g, activeRenderCamera->backgroundColor.b, activeRenderCamera->backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndScene()
    {
        BindFrameBuffer(0);
        glDisable(GL_DEPTH_TEST);

        glClearColor(0.f, 1.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (renderFrameBuffer)
        {
            screenShader.Use().Fatal("Renderer::EndScene()");
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

    Error Renderer::ActivateShader(Shader &shader)
    {
        Error err = shader.Use();
        if (err.HasError())
            return err;
        shader.SetMat4("projection", activeRenderCamera->projection);
        shader.SetMat4("view", activeRenderCamera->view);
        shader.SetVec3("viewPos", activeRenderCamera->GetPosition());

        return Error();
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
        // reinterpret_cast<ContextPtr *>(glfwGetWindowUserPointer(glfwWindow))->window->SetWindowSize({width, height});
        // reinterpret_cast<ContextPtr *>(glfwGetWindowUserPointer(glfwWindow))->renderer->SetViewport({width, height});
    }
}