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

#include <unordered_map>
#include <variant>

#include "core/asset.h"
#include "renderer/shader.h"
#include "renderer/texture.h"

namespace dt {
using uniform_value = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;

class material_t {
  public:
    asset<shader_t> shader_asset;
    std::unordered_map<std::string, asset<texture_t>> texture_assets;
    std::unordered_map<std::string, uniform_value> uniforms;

    material_t();

    static std::shared_ptr<material_t> load(const std::filesystem::path &path);
};
} // namespace dt