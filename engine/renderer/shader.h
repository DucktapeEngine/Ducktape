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

#include <filesystem>

#include <glm/glm.hpp>

#include "core/context.h"

namespace dt {
class shader_t {
  public:
    unsigned int id = 0;
    int compilation_status;

    shader_t(const std::unordered_map<GLenum, std::string> &shader_sources);
    ~shader_t();

    static std::shared_ptr<shader_t> load(const std::filesystem::path &path);

    void use() const;
    void set_bool(const std::string &name, const bool value);
    void set_int(const std::string &name, const int value);
    void set_float(const std::string &name, const float value);
    void set_vec2(const std::string &name, const glm::vec2 &value);
    void set_vec2(const std::string &name, const float x, const float y);
    void set_vec3(const std::string &name, const glm::vec3 &value);
    void set_vec3(const std::string &name, const float x, const float y, const float z);
    void set_vec4(const std::string &name, const glm::vec4 &value);
    void set_vec4(const std::string &name, const float x, const float y, const float z, const float w);
    void set_mat2(const std::string &name, const glm::mat2 &mat);
    void set_mat3(const std::string &name, const glm::mat3 &mat);
    void set_mat4(const std::string &name, const glm::mat4 &mat);

  private:
    static inline std::unordered_map<std::filesystem::path, shader_t> cache;
};
} // namespace dt