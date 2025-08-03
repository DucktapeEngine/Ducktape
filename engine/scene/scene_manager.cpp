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

#include "scene/scene_manager.h"

namespace dt {
void scene_manager_t::load_demo_scene() {
}

void scene_manager_t::load_scene() {
}

// void scene_manager_t::init(context_t *ctx) {
//     for (auto &system : systems.init)
//         system(ctx);
// }

// void scene_manager_t::tick(context_t *ctx, float delta_time) {
//     for (auto &system : systems.tick)
//         system(ctx, delta_time);
// }

// void scene_manager_t::render(context_t *ctx, float delta_time, const camera_component *camera_component) {
//     for (auto &system : systems.render)
//         system(ctx, delta_time, camera_component);
// }

// void scene_manager_t::inspector(context_t *ctx, float delta_time, entt::entity selected_entity) {
//     for (auto &system : systems.inspector)
//         system(ctx, delta_time, selected_entity);
// }
} // namespace dt