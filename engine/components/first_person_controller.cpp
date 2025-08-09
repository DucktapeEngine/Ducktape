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

#include "components/first_person_controller.h"
#include "components/camera.h"
#include "components/transform.h"
#include "scene/scene_manager.h"
#include "utils/math.h"

namespace dt {
void first_person_controller_component::move(const glm::vec3 input, const float speed, transform_component &transform) {
    transform.position += input.x * transform.right() * speed;
    transform.position += input.y * glm::vec3(0.f, 1.f, 0.f) * speed;
    transform.position += input.z * transform.forward() * speed;
}

void first_person_controller_component::look(const glm::vec2 input, const float sensitivity, transform_component &head_transform, transform_component &body_transform) {
    float mouse_x = input.x * sensitivity;
    float mouse_y = input.y * sensitivity;

    glm::quat yaw = glm::angleAxis(glm::radians(mouse_x), glm::vec3(0.f, 1.f, 0.f));
    glm::quat pitch = glm::angleAxis(glm::radians(-mouse_y), glm::vec3(1.f, 0.f, 0.f));

    body_transform.rotation = glm::normalize(yaw * body_transform.rotation);
    head_transform.rotation = glm::normalize(head_transform.rotation * pitch);
}

void first_person_controller_system_t::init(context_t *ctx) {
    glfwSetInputMode(ctx->window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto view = ctx->scene_manager->scene.view<first_person_controller_component>();

    for (auto [entity, first_person_controller] : view.each()) {
        std::ignore = ctx->scene_manager->scene.get_or_emplace<transform_component>(entity);
        std::ignore = ctx->scene_manager->scene.get_or_emplace<camera_component>(entity);
    }
}

void first_person_controller_system_t::tick(context_t *ctx, float dt) {
    auto view = ctx->scene_manager->scene.view<first_person_controller_component, transform_component, camera_component>();

    for (auto [entity, first_person_controller, transform, camera] : view.each()) {
        glm::vec3 move_input = {ctx->input_manager->is_key_down(KEY_A) * -1.0 + ctx->input_manager->is_key_down(KEY_D) * 1.f,
                                first_person_controller.can_fly ? (ctx->input_manager->is_key_down(KEY_LEFT_CONTROL) * -1.0 + ctx->input_manager->is_key_down(KEY_LEFT_SHIFT) * 1.f) : 0.f,
                                ctx->input_manager->is_key_down(KEY_S) * -1.0 + ctx->input_manager->is_key_down(KEY_W) * 1.f};
        first_person_controller_component::move(move_input, first_person_controller.speed * dt, transform);

        glm::vec2 look_input = ctx->input_manager->get_mouse_delta();
        first_person_controller_component::look(look_input, first_person_controller.sensitivity * dt, *first_person_controller.head_transform, *first_person_controller.body_transform);

        if (move_input.x != 0.f || move_input.y != 0.f || move_input.z != 0.f || look_input.x != 0.f || look_input.y != 0.f)
            camera.update_projection_view_matrix(ctx->window->size);
    }
}

void first_person_controller_system_t::inspector(context_t *ctx, float dt, entt::entity selected_entity) {
    auto view = ctx->scene_manager->scene.view<first_person_controller_component>();

    for (auto [entity, first_person_controller] : view.each()) {
        if (entity != selected_entity)
            continue;

        if (ImGui::CollapsingHeader("First Person Controller")) {
            ImGui::SeparatorText("Movement");
            ImGui::DragFloat("speed", &first_person_controller.speed);
            ImGui::SeparatorText("Look");
            ImGui::DragFloat("sensitivity", &first_person_controller.sensitivity);
        }
    }
}
} // namespace dt