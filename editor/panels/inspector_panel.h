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

#include "editor.h"
#include "panels/hierarchy_panel.h"
#include "panels/panel_base.h"

namespace dt {
class inspector_panel : public panel_base {
  public:
    void start(context_t *ctx) override {
        hierarchy = ctx->editor->get_panel<hierarchy_panel>();
    }

    void draw(context_t *ctx, float dt) override {
        ImGui::Begin("Inspector", &is_open);

        ctx->scene_manager->invoke_all(ctx->scene_manager->systems.inspector, stage_t::editor, ctx, dt, hierarchy->selected_entity);

        ImGui::End();
    }

  private:
    bool is_open = true;
    hierarchy_panel *hierarchy;
};
} // namespace dt