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

#include "panels/panel_base.h"

namespace dt {
class context_t;

class editor_t {
  public:
    std::vector<std::shared_ptr<panel_base>> panels;

    enum state {
        runtime,
        editor
    } current_state = state::editor;

    editor_t(const window_t &window);
    ~editor_t();

    template <typename T>
    T *get_panel() {
        for (auto &p : panels) {
            if (auto ptr = dynamic_cast<T *>(p.get())) {
                return ptr;
            }
        }
        return nullptr;
    }

    void new_frame();
    void end_frame();

    void start(context_t *ctx);
    void draw(context_t *ctx, float dt);

    void setup_ImGui_style();

  private:
    ImGuiID dockspace_id;
};
} // namespace dt