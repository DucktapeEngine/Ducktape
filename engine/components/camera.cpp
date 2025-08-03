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

#include "components/camera.h"
#include "components/transform.h"
#include "scene/scene_manager.h"

namespace dt {
void camera_component::update_projection_view_matrix(const glm::ivec2 &window_size) {
    view = glm::lookAtLH(shared_transform->translation, shared_transform->translation + shared_transform->forward(), shared_transform->up());

    float aspect = (float)window_size.x / (float)window_size.y;
    if (is_orthographic)
        projection = glm::orthoLH(-aspect, aspect, -1.0f, 1.0f, near_plane, far_plane);
    else
        projection = glm::perspectiveLH(glm::radians(field_of_view), aspect, near_plane, far_plane);
}

void camera_system_t::init(context_t *ctx) {
    auto scene_view = ctx->scene_manager->scene.view<camera_component>();

    for (auto [entity, camera] : scene_view.each()) {
        camera.shared_transform = &ctx->scene_manager->scene.get_or_emplace<transform_component>(entity);
        camera.render_target_window = ctx->window->handle;
    }
}

void camera_system_t::tick(context_t *ctx, float dt) {

    auto scene_view = ctx->scene_manager->scene.view<camera_component>();

    for (auto [entity, camera] : scene_view.each()) {
        camera.update_projection_view_matrix(ctx->window->size); // todo: avoid this heavy operation. without this, the camera doesn't reflect changes in the transform.
    }
}

void camera_system_t::inspector(context_t *ctx, float dt, entt::entity selected_entity) {
    auto view = ctx->scene_manager->scene.view<camera_component>();

    for (auto [entity, camera] : view.each()) {
        if (entity != selected_entity)
            continue;

        if (ImGui::CollapsingHeader("Camera")) {
            bool camera_needs_update = false;

            camera_needs_update |= ImGui::ColorEdit4("background", &camera.background_color.x);
            camera_needs_update |= ImGui::Checkbox("is orthographic", &camera.is_orthographic);
            camera_needs_update |= ImGui::DragFloat("field of view", &camera.field_of_view, 1.0f, 0.0f, 180.0f);
            camera_needs_update |= ImGui::DragFloat("near plane", &camera.near_plane);
            camera_needs_update |= ImGui::DragFloat("far plane", &camera.far_plane);

            if (camera_needs_update) {
                camera.update_projection_view_matrix(ctx->window->size);
            }
        }
    }
}
} // namespace dt