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

#include <string>

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#define IMGUI_VEC_DRAG_SPEED 0.1f

#include "core/asset.h"

namespace ImGui {
ImVec2 operator*(ImVec2 &iv2, float fl);
ImVec2 operator*(const ImVec2 &iv2, float fl);
ImVec2 operator*(ImVec2 &iv2, int i);
ImVec2 operator+(ImVec2 &iv2, ImVec2 &otheriv2);
ImVec2 operator+(const ImVec2 &iv2, const ImVec2 &otheriv2);

bool Vec2(const char *label, glm::vec2 *vec2, const float drag_speed = 0.1f);
bool Vec3(const char *label, glm::vec3 *vec3, const float drag_speed = 0.1f);
bool Color(const char *label, glm::vec3 *color, const float drag_speed = 1.0f);
bool Color(const char *label, glm::vec4 *color, const float drag_speed = 1.0f);

template <typename T>
void Asset(const char *label, ::dt::asset<T> *asset) {
    ImGui::InputText(label, &asset->path);
}
} // namespace ImGui