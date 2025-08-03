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

#include "scene/scene_manager.h"
#include "utils/sfinae.h"

namespace dt {
class camera_component;

DEFINE_HAS_METHOD_TRAIT(has_entity_init_method, init, void (T::*)(context_t *, entt::entity));
DEFINE_HAS_METHOD_TRAIT(has_entity_tick_method, tick, void (T::*)(context_t *, entt::entity, float));
DEFINE_HAS_METHOD_TRAIT(has_entity_inspector_method, inspector, void (T::*)(context_t *, entt::entity, float, entt::entity));
DEFINE_HAS_METHOD_TRAIT(has_entity_render_method, render, void (T::*)(context_t *, entt::entity, float, const camera_component *));

template <typename T>
class generic_system {
  public:
    void init(context_t *ctx) {
        auto view = ctx->scene_manager->scene.view<T>();
        for (auto entity : view)
            if constexpr (has_entity_init_method<T>::value)
                ctx->scene_manager->scene.get<T>(entity).init(ctx, entity);
    }

    void tick(context_t *ctx, float dt) {
        auto view = ctx->scene_manager->scene.view<T>();
        for (auto entity : view)
            if constexpr (has_entity_tick_method<T>::value)
                ctx->scene_manager->scene.get<T>(entity).tick(ctx, entity, dt);
    }

    void inspector(context_t *ctx, float dt, entt::entity selected_entity) {
        auto view = ctx->scene_manager->scene.view<T>();
        for (auto entity : view)
            if constexpr (has_entity_inspector_method<T>::value)
                ctx->scene_manager->scene.get<T>(entity).inspector(ctx, entity, dt, selected_entity);
    }

    void render(context_t *ctx, float dt, const camera_component *active_camera) {
        auto view = ctx->scene_manager->scene.view<T>();
        for (auto entity : view)
            if constexpr (has_entity_render_method<T>::value)
                ctx->scene_manager->scene.get<T>(entity).render(ctx, entity, dt, active_camera);
    }
};
} // namespace dt