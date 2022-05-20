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

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->window->windowSize.x),
                                          static_cast<float>(this->window->windowSize.y), 0.0f, -1.0f, 1.0f);

        shader.Use();
        shader.SetInt("image", 0);
        shader.SetMat4("projection", projection);
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
}