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

#include "components/transform.h"
#include "core/input_manager.h"
#include "core/window.h"
#include "scene/scene_manager.h"

namespace dt {
class transform_component;

class camera_component {
  public:
    float field_of_view = 75.f, near_plane = 0.1f, far_plane = 1000.f;
    glm::mat4 projection, view;
    bool is_orthographic = false;
    unsigned int fbo, rbo, render_texture;
    glm::vec4 background_color = glm::vec4(0.15f, 0.15f, 0.15f, 0.15f);
    GLFWwindow *render_target_window;

    transform_component *shared_transform;

    void update_projection_view_matrix(const glm::ivec2 &window_size);
};

class camera_system_t {
  public:
    void init(context_t *ctx);
    void tick(context_t *ctx, float dt);
    void inspector(context_t *ctx, float dt, entt::entity selected_entity);
};
} // namespace dt