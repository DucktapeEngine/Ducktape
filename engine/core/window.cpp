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

#include <fmt/format.h>

#include "core/context.h"
#include "core/log.h"
#include "core/window.h"
#include "renderer/renderer.h"

namespace dt {
window_t::window_t() {
    glfwInit();

    glfwSetErrorCallback((GLFWerrorfun)error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

    handle = glfwCreateWindow(1280, 720, "Ducktape Engine", nullptr, nullptr);
    if (handle == nullptr) {
        ERROR("failed to create glfw window");
        return;
    }

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    LOG("created glfw window");
}

window_t::~window_t() {
    glfwTerminate();
}

void window_t::error_callback(int code, const char *description) {
    ERROR("[glfw] [{}] {}", code, description);
}

void window_t::framebuffer_size_callback(GLFWwindow *glfwWindow, int width, int height) {
    context_t *context = reinterpret_cast<context_t *>(glfwGetWindowUserPointer(glfwWindow));
    context->renderer->update_viewport(glm::ivec2(width, height));
    context->window->size = {width, height};
}
} // namespace dt