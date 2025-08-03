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

#include <vector>

#include <entt/entt.hpp>

#include "core/log.h"
#include "core/stage.h"
#include "utils/sfinae.h"

namespace dt {
class context_t;
class camera_component;

template <typename T>
struct staged_delegate {
    stage_t stage;
    T delegate;
};

class system_group {
  public:
    std::vector<staged_delegate<entt::delegate<void(context_t *)>>> init;
    std::vector<staged_delegate<entt::delegate<void(context_t *, float)>>> tick;
    std::vector<staged_delegate<entt::delegate<void(context_t *, float, const camera_component *)>>> render;
    std::vector<staged_delegate<entt::delegate<void(context_t *, float, entt::entity)>>> inspector;
};

class scene_manager_t {
  public:
    entt::registry scene;
    system_group systems;

    void load_demo_scene();
    void load_scene();

    template <auto FnPtr, typename System, typename Delegate>
    void bind(System &sys, std::vector<staged_delegate<Delegate>> &list, stage_t stage) {
        Delegate delegate{};
        delegate.template connect<FnPtr>(sys);
        list.push_back({stage, delegate});
    }

    template <typename... Args, typename Delegate>
    void invoke_all(std::vector<staged_delegate<Delegate>> &list, stage_t active_stage, Args &&...args) {
        for (auto &entry : list) {
            if (entry.stage == stage_t::both || entry.stage == active_stage)
                entry.delegate(std::forward<Args>(args)...);
        }
    }
};
} // namespace dt