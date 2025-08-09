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

#include "components/joint.h"
#include "core/context.h"
#include "scene/scene_manager.h"

namespace dt {
void joint_system_t::tick(context_t *ctx, float dt) {
    auto scene_view = ctx->scene_manager->scene.view<transform_component, joint_component>();

    for (auto [entity, transform, joint] : scene_view.each()) {
        transform.position = joint.joined_transform->position + joint.offset.position;
    }
}

void joint_system_t::inspector(context_t *ctx, float dt, entt::entity selected_entity) {
    auto view = ctx->scene_manager->scene.view<joint_component>();

    for (auto [entity, camera] : view.each()) {
        if (entity != selected_entity)
            continue;

        if (ImGui::CollapsingHeader("Joint")) {
            // todo: some better way to render components (architectural haul)
        }
    }
}
} // namespace dt