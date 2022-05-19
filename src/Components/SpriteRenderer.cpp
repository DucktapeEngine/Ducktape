/*
MIT License

Copyright (c) 2022 Ducktape

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