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

#include "core/input_manager.h"
#include <glm/gtx/string_cast.hpp>

namespace dt {
input_manager_t::input_manager_t(window_t *window) : window(window) {
    glfwSetKeyCallback(window->handle, key_callback);
    glfwSetMouseButtonCallback(window->handle, mouse_button_callback);

    glfwPollEvents(); // helps fetch initial state
    double cur_pos_x, cur_pos_y;
    glfwGetCursorPos(window->handle, &cur_pos_x, &cur_pos_y);
    mouse_position = glm::vec2(cur_pos_x, cur_pos_y);
    mouse_delta = glm::vec2(0.0f);

    std::fill(std::begin(key_down), std::end(key_down), false);
    std::fill(std::begin(key_down_prev), std::end(key_down_prev), false);
    std::fill(std::begin(mouse_down), std::end(mouse_down), false);
    std::fill(std::begin(mouse_down_prev), std::end(mouse_down_prev), false);
}

void input_manager_t::process_input() {
    double cur_pos_x, cur_pos_y;
    glfwGetCursorPos(window->handle, &cur_pos_x, &cur_pos_y);

    mouse_delta = glm::vec2(cur_pos_x - mouse_position.x, mouse_position.y - cur_pos_y);
    mouse_position = glm::vec2(cur_pos_x, cur_pos_y);
}

void input_manager_t::clear_tick_state() {
    std::copy(std::begin(key_down), std::end(key_down), std::begin(key_down_prev));
    std::copy(std::begin(mouse_down), std::end(mouse_down), std::begin(mouse_down_prev));
    mouse_delta = glm::vec2(0.0f);
}

glm::vec2 input_manager_t::get_mouse_position() {
    return mouse_position;
}

glm::vec2 input_manager_t::get_mouse_delta() {
    return mouse_delta;
}

bool input_manager_t::is_mouse_down(int button) {
    return mouse_down[button];
}

bool input_manager_t::is_key_down(int key) {
    return key_down[key];
}

bool input_manager_t::was_key_pressed(int key) {
    return key_down[key] && !key_down_prev[key];
}

bool input_manager_t::was_key_released(int key) {
    return !key_down[key] && key_down_prev[key];
}

void input_manager_t::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key < 0 || key >= MAX_KEYS)
        return;

    context_t *ctx = reinterpret_cast<context_t *>(glfwGetWindowUserPointer(window));
    input_manager_t *input = ctx->input_manager;

    if (action == GLFW_PRESS)
        input->key_down[key] = true;
    else if (action == GLFW_RELEASE)
        input->key_down[key] = false;
}

void input_manager_t::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button < 0 || button >= MAX_MOUSE_BUTTONS)
        return;

    context_t *ctx = reinterpret_cast<context_t *>(glfwGetWindowUserPointer(window));
    input_manager_t *input = ctx->input_manager;

    if (action == GLFW_PRESS)
        input->mouse_down[button] = true;
    else if (action == GLFW_RELEASE)
        input->mouse_down[button] = false;
}

} // namespace dt