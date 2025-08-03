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

#include <imguizmo/ImGuizmo.h>
#include <utils/imgui.h>

#include "components/camera.h"
#include "editor.h"
#include "panels/hierarchy_panel.h"
#include "panels/panel_base.h"

namespace dt {
class world_view_panel : public panel_base {
  public:
    const float speed = 5.0f, sensitivity = 25.0f;

    void start(context_t *ctx) override {
        hierarchy = ctx->editor->get_panel<hierarchy_panel>();
        input = ctx->input_manager;
        scene_manager = ctx->scene_manager;
    }

    void draw(context_t *ctx, float dt) override {
        auto view = ctx->scene_manager->scene.view<camera_component, transform_component>();
        auto entity = view.front();
        if (entity == entt::null)
            return;
        auto &transform = ctx->scene_manager->scene.get<transform_component>(entity);
        auto &camera = ctx->scene_manager->scene.get<camera_component>(entity);

        handle_fps_camera_controls(ctx, dt, transform, camera);

        ImGuizmo::BeginFrame();
        ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
        ImGuizmo::SetRect(0, 0, ctx->window->size.x, ctx->window->size.y);
        ImGuizmo::SetOrthographic(camera.is_orthographic);

        // todo: custom grid renderer implementation

        draw_transform_gizmo(camera);

        render_toolbar_panel();
    }

    void handle_fps_camera_controls(context_t *ctx, float dt, transform_component &transform, camera_component &camera) {
        glm::vec3 move_input = {ctx->input_manager->is_key_down(KEY_A) * -1.0 + ctx->input_manager->is_key_down(KEY_D) * 1.0f,
                                ctx->input_manager->is_key_down(KEY_LEFT_CONTROL) * -1.0 + ctx->input_manager->is_key_down(KEY_LEFT_SHIFT) * 1.0f,
                                ctx->input_manager->is_key_down(KEY_S) * -1.0 + ctx->input_manager->is_key_down(KEY_W) * 1.0f};
        first_person_controller_component::move(move_input, speed * dt, transform);

        glm::vec2 look_input = ctx->input_manager->get_mouse_delta() * (ctx->input_manager->is_mouse_down(MOUSE_BUTTON_RIGHT) ? 1.0f : 0.0f);
        first_person_controller_component::look(look_input, sensitivity * dt, transform);

        if (move_input.x != 0.0f || move_input.y != 0.0f || move_input.z != 0.0f || look_input.x != 0.0f || look_input.y != 0.0f)
            camera.update_projection_view_matrix(ctx->window->size);
    }

    void draw_transform_gizmo(camera_component &camera) {
        if (scene_manager->scene.valid(hierarchy->selected_entity) && scene_manager->scene.any_of<transform_component>(hierarchy->selected_entity)) {
            transform_component &transform = scene_manager->scene.get<transform_component>(hierarchy->selected_entity);

            float snap = 1.f;
            if (gizmo_operation == ImGuizmo::OPERATION::ROTATE)
                snap = 45.f;

            glm::mat4 model = transform.get_model_matrix();
            ImGuizmo::Manipulate(glm::value_ptr(camera.view), glm::value_ptr(camera.projection), gizmo_operation, gizmo_mode, glm::value_ptr(model), NULL, input->is_key_down(KEY_LEFT_ALT) ? &snap : NULL);
            if (ImGuizmo::IsUsing())
                transform.set_model_matrix(model);
        }
    }

    void render_toolbar_panel() {
        ImGui::Begin("World View", &is_open);

        if (ImGui::RadioButton("Translate", gizmo_operation == ImGuizmo::TRANSLATE))
            gizmo_operation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Rotate", gizmo_operation == ImGuizmo::ROTATE))
            gizmo_operation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Scale", gizmo_operation == ImGuizmo::SCALE))
            gizmo_operation = ImGuizmo::SCALE;

        if (ImGui::RadioButton("World", gizmo_mode == ImGuizmo::WORLD))
            gizmo_mode = ImGuizmo::WORLD;
        ImGui::SameLine();
        if (ImGui::RadioButton("Local", gizmo_mode == ImGuizmo::LOCAL))
            gizmo_mode = ImGuizmo::LOCAL;

        ImGui::End();
    }

  private:
    hierarchy_panel *hierarchy;
    input_manager_t *input;
    scene_manager_t *scene_manager;
    glm::vec3 orientation;

    ImGuizmo::OPERATION gizmo_operation = ImGuizmo::TRANSLATE;
    ImGuizmo::MODE gizmo_mode = ImGuizmo::WORLD;
};
} // namespace dt