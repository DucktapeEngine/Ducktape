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

#include <Components/SpriteRenderer.h>

namespace Ducktape
{
    void SpriteRenderer::Init()
    {
        if (sprite != "")
            texture.Load(sprite);

        transform = &Entity::FromComponent(*this).GetComponent<Transform>();

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(engine->window.windowSize.x),
                                          static_cast<float>(engine->window.windowSize.y), 0.0f, -1.0f, 1.0f);

        engine->renderer.shader.Use();
        engine->renderer.shader.SetInt("image", 0);
        engine->renderer.shader.SetMat4("projection", projection);
    }

    void SpriteRenderer::Tick()
    {
        engine->renderer.shader.Use(); // TOFIX: Change this to seperate shader for each SpriteRenderer

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(transform->position, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

        model = glm::translate(model, glm::vec3(0.5f * transform->scale.x, 0.5f * transform->scale.y, 0.0f));   // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(transform->rotation), glm::vec3(0.0f, 0.0f, 1.0f));             // then rotate
        model = glm::translate(model, glm::vec3(-0.5f * transform->scale.x, -0.5f * transform->scale.y, 0.0f)); // move origin back

        model = glm::scale(model, glm::vec3(transform->scale, 1.0f)); // last scale

        engine->renderer.shader.SetMat4("model", model);

        // render textured quad
        engine->renderer.shader.SetVec3("spriteColor", color);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}