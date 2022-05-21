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

namespace Ducktape
{
    void Renderer::Init(Window &window)
    {
        FT("Renderer::Init()");

        this->window = &window;
        shader.Load("../shaders/vertex.glsl", "../shaders/fragment.glsl");

        projection = glm::ortho(0.0f, static_cast<float>(this->window->windowSize.x),
                                static_cast<float>(this->window->windowSize.y), 0.0f, -1.0f, 1.0f);

        shader.Use();
        shader.SetInt("image", 0);
        shader.SetMat4("projection", projection);

        if (renderWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::Clear()
    {
        FT("Renderer::Clear()");

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Flush()
    {
        FT("Renderer::Flush()");

        glfwSwapBuffers(window->window);
    }

    void Renderer::DrawQuad(const glm::vec2 &position, const float &rotation, const glm::vec2 &scale, const Color &color, Texture &texture, unsigned int &VAO, const Transform &camera)
    {
        shader.Use(); // TOFIX: Change this so that SpriteRenderers have their own shader

        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(camera.position, 0.0f));
        view = glm::rotate(view, glm::radians(camera.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::scale(view, glm::vec3(camera.scale, 1.0f));

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(position, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

        model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));   // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
        model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // move origin back

        model = glm::scale(model, glm::vec3(scale, 1.0f)); // last scale

        shader.SetMat4("view", view);
        shader.SetMat4("model", model);
        shader.SetVec3("spriteColor", (glm::vec4)color);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}