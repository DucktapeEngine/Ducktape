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

#include "components/tag.h"
#include "panels/panel_base.h"
#include "scene/scene_manager.h"

namespace dt {
class hierarchy_panel : public panel_base {
  public:
    entt::entity selected_entity = entt::null;

    void start(context_t *ctx) override {
        scene_manager = ctx->scene_manager;
    }

    void draw(context_t *ctx, float dt) override {
        ImGui::Begin("Hierarchy", &is_open);

        for (auto entity : scene_manager->scene.view<entt::entity>()) {
            std::string label;

            auto *tag = scene_manager->scene.try_get<tag_component>(entity);

            if (tag != nullptr)
                label = tag->name;
            else
                label = "entity " + std::to_string((ENTT_ID_TYPE)entity);

            if (ImGui::Selectable((label + "##" + std::to_string((ENTT_ID_TYPE)entity)).c_str(), selected_entity == entity))
                selected_entity = entity;
        }

        // // entity control
        // if (ImGui::Button("create entity", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
        //     selected_entity = scene_manager->active_scene.create_entity();
        // if (ImGui::Button("destroy entity", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
        //     scene_manager->active_scene.destroy_entity(selected_entity);

        // // entity list
        // for (entt::entity entity : scene_manager->active_scene.get_entities()) {
        // }

        ImGui::End();
    }

  private:
    scene_manager_t *scene_manager;

    friend class inspector_panel;
};
} // namespace dt