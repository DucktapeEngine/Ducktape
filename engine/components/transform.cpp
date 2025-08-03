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

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <utils/imgui.h>
#include <utils/math.h>

#include "components/transform.h"
#include "core/context.h"
#include "scene/scene_manager.h"

namespace dt {
glm::mat4 transform_component::get_model_matrix() const {
    glm::mat4 trans = glm::translate(glm::mat4(1.f), translation);
    glm::mat4 rot = glm::toMat4(rotation);
    glm::mat4 scl = glm::scale(glm::mat4(1.f), scale);

    return trans * rot * scl;
}

void transform_component::set_model_matrix(glm::mat4 model) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(model, scale, rotation, translation, skew, perspective);
}

glm::vec3 transform_component::right() const {
    return rotation * glm::vec3(1.f, 0.f, 0.f);
}

glm::vec3 transform_component::forward() const {
    return rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 transform_component::up() const {
    return rotation * glm::vec3(0.f, 1.f, 0.f);
}

glm::vec3 transform_component::get_euler_rotation() const {
    return glm::degrees(glm::eulerAngles(rotation));
}

void transform_component::set_euler_rotation(glm::vec3 euler_rotation) {
    rotation = glm::radians(euler_rotation);
}

void transform_component::look_at(const glm::vec3 &at) {
    rotation = glm::quatLookAt(glm::normalize(at - translation), {0.f, 1.f, 0.f});
}

void transform_system_t::inspector(context_t *ctx, float dt, entt::entity selected_entity) {
    auto view = ctx->scene_manager->scene.view<transform_component>();

    for (auto [entity, transform_component] : view.each()) {
        if (entity != selected_entity)
            continue;

        if (ImGui::CollapsingHeader("Transform")) {
            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Reset")) {
                    transform_component.translation = glm::vec3(0);
                    transform_component.set_euler_rotation(glm::vec3(0));
                    transform_component.scale = glm::vec3(1);
                }
                ImGui::EndPopup();
            }

            ImGui::Vec3("position", &transform_component.translation);

            glm::vec3 euler_angles = transform_component.get_euler_rotation();
            if (ImGui::Vec3("rotation", &euler_angles))
                transform_component.set_euler_rotation(euler_angles);

            ImGui::Vec3("scale", &transform_component.scale);
        }
    }
}
} // namespace dt