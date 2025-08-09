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

#include <tracy/Tracy.hpp>

#include "components/tag.h"
#include "core/log.h"
#include "renderer/renderer.h"
#include "scene/scene_manager.h"

GLenum glCheckError_(const char *file, int line) {
    GLenum error_code;
    while ((error_code = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (error_code) {
        case GL_INVALID_ENUM:
            error = "[INVALID_ENUM]";
            break;
        case GL_INVALID_VALUE:
            error = "[INVALID_VALUE]";
            break;
        case GL_INVALID_OPERATION:
            error = "[INVALID_OPERATION]";
            break;
        case GL_OUT_OF_MEMORY:
            error = "[OUT_OF_MEMORY]";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "[INVALID_FRAMEBUFFER_OPERATION]";
            break;
        }
        std::cout << "" << error << " [" << file << "] [" << line << "]\n";
    }
    return error_code;
}

namespace dt {
renderer_t::renderer_t(window_t *window) : window(window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ERROR("failed to initialize glad.");
        return;
    }
    LOG("initialized glad.");

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_output, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    update_viewport();
}

void renderer_t::update_shader_uniforms(shader_t &shader, const camera_component *active_camera) {
    shader.use();
    shader.set_mat4("projection", active_camera->projection);
    shader.set_mat4("view", active_camera->view);
    shader.set_vec3("view_pos", active_camera->shared_transform->position);
}

void renderer_t::render(context_t &ctx, float dt) {
    ZoneScoped;

    auto scene_view = ctx.scene_manager->scene.view<camera_component>();

    for (auto [entity, camera] : scene_view.each()) {
        assert(camera.render_target_window != nullptr);

        glfwMakeContextCurrent(camera.render_target_window);

        glClearColor(camera.background_color.r, camera.background_color.g, camera.background_color.b, camera.background_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ctx.scene_manager->invoke_all(ctx.scene_manager->systems.render, stage_t::both, &ctx, dt, &camera);
    }
}

void renderer_t::draw(const glm::mat4 &model, const mesh_t &draw_mesh, material_t &material) {
    std::shared_ptr<shader_t> active_shader = material.shader_asset.get();

    if (material.uniforms.find("color") != material.uniforms.end())
        active_shader->set_vec3("material.color", std::get<glm::vec3>(material.uniforms.at("color")));
    if (material.uniforms.find("shininess") != material.uniforms.end())
        active_shader->set_float("material.shininess", std::get<float>(material.uniforms.at("shininess")));
    active_shader->set_mat4("model", model);

    int current_texture_index = 0;

    for (auto &texture_asset : material.texture_assets) {
        glActiveTexture(GL_TEXTURE0 + current_texture_index);
        glBindTexture(GL_TEXTURE_2D, texture_asset.second->id);
        active_shader->set_int("material." + texture_asset.first, current_texture_index);
        current_texture_index++;
    }

    glBindVertexArray(draw_mesh.vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(draw_mesh.indices.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void renderer_t::update_viewport() {
    update_viewport(window->size);
}

void renderer_t::update_viewport(glm::ivec2 viewport_size) {
    glViewport(0, 0, viewport_size.x, viewport_size.y);
}

bool renderer_t::get_free_directional_light_spot(unsigned int *spot) {
    for (int i = 0; i < MAX_LIGHT_NO; i++) {
        if (occupied_directional_lights[i] == false) {
            occupied_directional_lights[i] = true;
            *spot = i;
            return true;
        }
    }
    return false;
}

void renderer_t::unoccupy_directional_light_spot(unsigned int spot) {
    occupied_directional_lights[spot] = false;
}

bool renderer_t::get_free_point_light_spot(unsigned int *spot) {
    for (int i = 0; i < MAX_LIGHT_NO; i++) {
        if (occupied_point_lights[i] == false) {
            occupied_point_lights[i] = true;
            *spot = i;
            return true;
        }
    }
    return false;
}

void renderer_t::unoccupy_point_light_spot(unsigned int spot) {
    occupied_point_lights[spot] = false;
}

void APIENTRY renderer_t::gl_debug_output(GLenum source_enum, GLenum type_enum, GLuint id, GLenum severity_enum, GLsizei length, const GLchar *message, const void *userParam) {
    // UNUSED(length);
    // UNUSED(user_param);

    // if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    if (message[22] == 'G' || message[22] == 'D')
        return;

    std::string severity;
    std::string source;
    std::string type;

    switch (severity_enum) {
    case GL_DEBUG_SEVERITY_HIGH:
        severity = "FATAL";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity = "WARN";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        severity = "WARN";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity = "NOTE";
        break;
    }

    switch (source_enum) {
    case GL_DEBUG_SOURCE_API:
        source = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source = "Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source = "Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source = "Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source = "Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source = "Other";
        break;
    }

    switch (type_enum) {
    case GL_DEBUG_TYPE_ERROR:
        type = "Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type = "Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type = "Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type = "Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type = "Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        type = "Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type = "Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type = "Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type = "Other";
        break;
    }

    std::string error = fmt::format("[{}] [id:{}] [{}] [{}]\n{}", severity, id, source, type, message);
    std::cout << error << std::endl;
}
} // namespace dt