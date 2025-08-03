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

#include "renderer/shader.h"
#include "core/asset.h"
#include "core/context.h"
#include "core/log.h"

namespace dt {
shader_t::shader_t(const std::unordered_map<GLenum, std::string> &shader_sources) {
    std::vector<unsigned int> shader_ids;

    for (const auto &[type, source] : shader_sources) {
        unsigned int shader_id = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(shader_id, 1, &src, nullptr);
        glCompileShader(shader_id);

        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_status);
        if (!compilation_status) {
            char info_log[512];
            glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
            ERROR("shader compilation failed: {}", info_log);
            return;
        }

        shader_ids.push_back(shader_id);
    }

    id = glCreateProgram();
    for (auto shader_id : shader_ids)
        glAttachShader(id, shader_id);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &compilation_status);
    if (!compilation_status) {
        char info_log[512];
        glGetProgramInfoLog(id, 512, nullptr, info_log);
        ERROR("shader program linking failed: {}", info_log);
    }

    for (auto shader_id : shader_ids)
        glDeleteShader(shader_id);

    LOG("linked shader program with id {}", id);
}

shader_t::~shader_t() {
    glDeleteProgram(id);
    LOG("deleted shader program with id {}", id);
}

std::shared_ptr<shader_t> shader_t::load(const std::filesystem::path &path) {
    static std::unordered_map<std::string, std::shared_ptr<shader_t>> cache;

    std::string key = path.string();
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        ERROR("failed to open shader file: {}", path.string());
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string src = buffer.str();

    std::unordered_map<GLenum, std::string> result;
    size_t pos = 0;

    while (pos < src.size()) {
        size_t type_pos = src.find("#type", pos);
        if (type_pos == std::string::npos)
            break;

        size_t eol = src.find('\n', type_pos);
        std::string type_str = src.substr(type_pos + 6, eol - type_pos - 6);
        GLenum stage;

        if (type_str.find("vertex") != std::string::npos)
            stage = GL_VERTEX_SHADER;
        else if (type_str.find("fragment") != std::string::npos)
            stage = GL_FRAGMENT_SHADER;
        else if (type_str.find("geometry") != std::string::npos)
            stage = GL_GEOMETRY_SHADER;
        else {
            pos = eol + 1;
            continue;
        }

        size_t next_type = src.find("#type", eol);
        std::string shader_src = src.substr(eol + 1, next_type - eol - 1);
        result[stage] = shader_src;
        pos = next_type;
    }

    auto shader_ptr = std::make_shared<shader_t>(result);
    cache[key] = shader_ptr;
    return shader_ptr;
}

void shader_t::use() const {
    glUseProgram(id);
}

void shader_t::set_bool(const std::string &name, const bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void shader_t::set_int(const std::string &name, const int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void shader_t::set_float(const std::string &name, const float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader_t::set_vec2(const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void shader_t::set_vec2(const std::string &name, const float x, const float y) {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void shader_t::set_vec3(const std::string &name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void shader_t::set_vec3(const std::string &name, const float x, const float y, const float z) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void shader_t::set_vec4(const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void shader_t::set_vec4(const std::string &name, const float x, const float y, const float z, const float w) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void shader_t::set_mat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void shader_t::set_mat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void shader_t::set_mat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
} // namespace dt