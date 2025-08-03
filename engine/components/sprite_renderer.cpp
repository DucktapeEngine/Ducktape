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

#include <utils/imgui.h>

#include "components/sprite_renderer.h"
#include "components/transform.h"
#include "core/context.h"
#include "core/log.h"
#include "renderer/renderer.h"
#include "scene/scene_manager.h"

namespace dt {
void sprite_renderer_component::set_sprite(const std::string &path) {
    material_asset->texture_assets.emplace("diffuse", asset<texture_t>(path));
}

void sprite_renderer_system_t::init(context_t *ctx) {
    auto view = ctx->scene_manager->scene.view<sprite_renderer_component>();

    for (auto [entity, sprite_renderer] : view.each()) {
        sprite_renderer.material_asset.copy();
    }
}

void sprite_renderer_system_t::render(context_t *ctx, float dt, const camera_component *active_camera) {
    auto view = ctx->scene_manager->scene.view<sprite_renderer_component>();

    for (auto [entity, sprite_renderer] : view.each()) {
        if (sprite_renderer.material_asset.has()) {
            transform_component &transform = ctx->scene_manager->scene.get_or_emplace<transform_component>(entity);
            ctx->renderer->update_shader_uniforms(sprite_renderer.material_asset->shader_asset.get(), active_camera);
            ctx->renderer->draw(transform.get_model_matrix(), sprite_renderer.mesh, sprite_renderer.material_asset.get());
        }
    }
}

void sprite_renderer_system_t::inspector(context_t *ctx, float dt, entt::entity selected_entity) {
    auto view = ctx->scene_manager->scene.view<sprite_renderer_component>();

    for (auto [entity, sprite_renderer] : view.each()) {
        if (entity != selected_entity)
            continue;

        if (ImGui::CollapsingHeader("Sprite Renderer")) {
            // ImGui::Asset("material", &sprite_renderer.material_asset);
        }
    }
}
} // namespace dt