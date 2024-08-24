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

#pragma once

#define MAX_LIGHT_NO 25

#include <Components/Camera.h>
#include <Core/Error.h>
#include <Core/Context.h>
#include <Core/Window.h>
#include <Renderer/Shader.h>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace DT
{
    class Renderer
    {
    public:
        Renderer(Context &ctx, const json &rendererData);

        void BeginScene(BaseCamera *camera);
        void EndScene();

        void SetViewport(const glm::vec2 &newViewportSize);

        Error ActivateShader(Shader &shader);
        
        bool GetFreeDirectionalLightSpot(unsigned int *spot);
		void UnoccupyDirectionalLightSpot(unsigned int spot);
		bool GetFreePointLightSpot(unsigned int *spot);
		void UnoccupyPointLightSpot(unsigned int spot);

        void SetRenderFrameBuffer(bool flag)
        {
            renderFrameBuffer = flag;
        }

        void BindFrameBuffer(unsigned int fbo)
        {
            if (bindedFBO == fbo)
                return;
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            bindedFBO = fbo;
        }

        glm::vec2 GetViewportSize()
        {
            return viewportSize;
        }

        BaseCamera *GetActiveRenderCamera()
        {
            return activeRenderCamera;
        }

		static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    
    private:
        glm::vec2 viewportSize;
        BaseCamera *activeRenderCamera;

        unsigned int bindedFBO = 0;

        bool renderFrameBuffer = true;
        unsigned int quadVAO, quadVBO;

        std::array<bool, MAX_LIGHT_NO> occupiedDirectionalLights = {false};
        std::array<bool, MAX_LIGHT_NO> occupiedPointLights = {false};
        Window *window;

        Shader screenShader;
    };
}