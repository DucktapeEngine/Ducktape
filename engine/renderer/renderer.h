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

#pragma once

#define MAX_LIGHT_NO 25

// todo: remove unnecessary includes from headers and move it to source files across all files
#include "components/camera.h"
#include "core/window.h"
#include "renderer/material.h"
#include "renderer/mesh.h"
#include "renderer/shader.h"

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace dt {
class renderer_t {
  public:
    renderer_t(window_t *window);

    void update_shader_uniforms(shader_t &shader, const camera_component *active_camera);
    void render(context_t &ctx, float delta);
    void draw(const glm::mat4 &model, const mesh_t &draw_mesh, material_t &material);

    void update_viewport();
    void update_viewport(glm::ivec2 viewport_size);

    // todo: mark appropriate functions as const across all files
    bool get_free_directional_light_spot(unsigned int *spot);
    void unoccupy_directional_light_spot(unsigned int spot);
    bool get_free_point_light_spot(unsigned int *spot);
    void unoccupy_point_light_spot(unsigned int spot);

    static void APIENTRY gl_debug_output(GLenum source_enum, GLenum type_enum, GLuint id, GLenum severity_enum, GLsizei length, const GLchar *message, const void *userParam);

  private:
    std::array<bool, MAX_LIGHT_NO> occupied_directional_lights = {false};
    std::array<bool, MAX_LIGHT_NO> occupied_point_lights = {false};

    // todo: use m_ prefix for private members
    const window_t *window;
};
} // namespace dt