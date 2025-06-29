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

#include <utils/imgui.h>

void ImGui::Vec3(const std::string &label, glm::vec3 &vec3)
{
    ImGui::DragFloat3(label.c_str(), &vec3.x);
}

void ImGui::Vec2(const std::string &label, glm::vec2 &vec2)
{
    ImGui::DragFloat2(label.c_str(), &vec2.x);
}

void ImGui::Color(const std::string &label, glm::vec3 &color)
{
    ImGui::ColorEdit3(label.c_str(), &color.x);
}

void ImGui::Color(const std::string &label, glm::vec4 &color)
{
    ImGui::ColorEdit4(label.c_str(), &color.x);
}

ImVec2 ImGui::operator*(ImVec2 &iv2, float fl)
{
    return {iv2.x * fl, iv2.y * fl};
}

ImVec2 ImGui::operator*(const ImVec2 &iv2, float fl)
{
    return {iv2.x * fl, iv2.y * fl};
}

ImVec2 ImGui::operator*(ImVec2 &iv2, int i)
{
    return {iv2.x * i, iv2.y * i};
}

ImVec2 ImGui::operator+(ImVec2 &iv2, ImVec2 &otheriv2)
{
    return {iv2.x + otheriv2.x, iv2.y + otheriv2.y};
}

ImVec2 ImGui::operator+(const ImVec2 &iv2, const ImVec2 &otheriv2)
{
    return {iv2.x + otheriv2.x, iv2.y + otheriv2.y};
}