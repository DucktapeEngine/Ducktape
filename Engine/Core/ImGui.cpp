/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Core/ImGui.h>

void ImGui::Material(const std::string &label, DT::Material *material)
{
    ImGui::Indent();
    if (ImGui::CollapsingHeader(label.c_str()))
    {
        ImGui::ColorEdit3("color", &material->ambientColor.x);
        ImGui::ColorEdit3("color", &material->diffuseColor.x);
        ImGui::ColorEdit3("color", &material->specularColor.x);
        ImGui::DragFloat("shininess", &material->shininess);
    }
    ImGui::Unindent();
}

void ImGui::Vec3(const std::string &label, glm::vec3 *vec3)
{
    ImGui::DragFloat3(label.c_str(), &vec3->x);
}

void ImGui::Vec2(const std::string &label, glm::vec2 *vec2)
{
    ImGui::DragFloat2(label.c_str(), &vec2->x);
}

void ImGui::Color(const std::string &label, glm::vec3 *color)
{
    ImGui::ColorEdit3(label.c_str(), &color->x);
}

void ImGui::Color(const std::string &label, glm::vec4 *color)
{
    ImGui::ColorEdit4(label.c_str(), &color->x);
}

bool ImGui::ImageButtonWithText(ImTextureID texId, const char *label, const ImVec2 &imageSize, bool wrapContent, const ImVec2 &uv0, const ImVec2 &uv1, int frame_padding, const ImVec4 &bg_col, const ImVec4 &tint_col)
{
    ImGuiWindow *window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImVec2 size = imageSize;
    if (size.x <= 0 && size.y <= 0)
    {
        size.x = size.y = ImGui::GetTextLineHeightWithSpacing();
    }
    else
    {
        if (size.x <= 0)
            size.x = size.y;
        else if (size.y <= 0)
            size.y = size.x;
        size = size * window->FontWindowScale * ImGui::GetIO().FontGlobalScale;
    }

    ImGuiContext &g = *GImGui;
    const ImGuiStyle &style = g.Style;

    const ImGuiID id = window->GetID(label);
    const ImVec2 textSize = ImGui::CalcTextSize(label, NULL, true);
    const bool hasText = textSize.x > 0;
    float fillX = GetContentRegionAvail().x;
    float fillY = size.y + textSize.y;

    const float innerSpacing = hasText ? ((frame_padding >= 0) ? (float)frame_padding : (style.ItemInnerSpacing.x)) : 0.f;
    ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
    ImVec2 totalSizeWithoutPadding(wrapContent ? size.x + innerSpacing + imageSize.x : fillX, wrapContent ? fillY : size.y > textSize.y ? size.y
                                                                                                                                        : textSize.y);
    ImRect bb(window->DC.CursorPos, window->DC.CursorPos + totalSizeWithoutPadding + padding * 2);
    ImVec2 bbSize = bb.GetSize();
    ImVec2 start(0, 0);
    start = window->DC.CursorPos + padding;
    if (size.y < textSize.y)
        start.y += (textSize.y - size.y) * .5f;
    if (wrapContent)
        start.x += (bbSize.x - imageSize.x) / 2;

    const ImRect image_bb(start, start + size);
    start = window->DC.CursorPos + padding;
    if (!wrapContent)
        start.x += size.x + innerSpacing;
    if (!wrapContent && size.y > textSize.y)
        start.y += (size.y - textSize.y) * .5f;
    ItemSize(bb);
    if (!ItemAdd(bb, id))
        return false;

    bool hovered = false, held = false;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    // Render
    const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered
                                                                                      : ImGuiCol_Button);
    RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
    if (bg_col.w > 0.0f)
        window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));

    window->DrawList->AddImage(texId, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

    if (textSize.x > 0)
    {
        if (wrapContent)
        {
            start.y += size.y - (innerSpacing - (textSize.y / 2));
            start.x += (textSize.x >= bbSize.x ? 0 : bbSize.x - textSize.x - innerSpacing) / 2;
            float ellipsisPadding = 10.0f;
            // ImGui::RenderTextClipped()
            float ellipsis_max_x = (start + totalSizeWithoutPadding).x + ellipsisPadding;
            ImGui::RenderTextEllipsis(window->DrawList, start, start + totalSizeWithoutPadding, ellipsis_max_x, ellipsis_max_x, label, NULL, NULL);
            // ImGui::RenderText(start,label);
        }
        else
            ImGui::RenderText(start, label);
    }
    return pressed;
}
/// @brief This custom widget is not working properly as intended as because ImGui internal stuff
/// is complicated about how to draw multiple items in same rect.
bool ImGui::ImageWithInputText(ImTextureID texId, const char* label, char* buf, size_t buf_size, const ImVec2& imageSize, const ImVec2& uv0, const ImVec2& uv1, bool wrapContent,int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImVec2 size = imageSize;
    if (size.x <= 0 && size.y <= 0)
    {
        size.x = size.y = ImGui::GetTextLineHeightWithSpacing();
    }
    else
    {
        if (size.x <= 0)
            size.x = size.y;
        else if (size.y <= 0)
            size.y = size.x;
        size = size * window->FontWindowScale * ImGui::GetIO().FontGlobalScale;
    }

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    const ImGuiID id = window->GetID(label);
    const ImVec2 textSize = ImGui::CalcTextSize("InputText", NULL, true);
    const bool hasText = textSize.x > 0;
    float fillX = GetContentRegionAvail().x;
    float fillY = size.y + textSize.y;

    const float innerSpacing = hasText ? ((frame_padding >= 0) ? (float)frame_padding : (style.ItemInnerSpacing.x)) : 0.f;
    ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
    ImVec2 totalSizeWithoutPadding(wrapContent ? size.x + innerSpacing + imageSize.x : fillX, wrapContent ? fillY : size.y > textSize.y ? size.y
        : textSize.y);
    ImRect bb(window->DC.CursorPos, window->DC.CursorPos + totalSizeWithoutPadding + padding * 2);
    ImVec2 bbSize = bb.GetSize();
    ImVec2 start(0, 0);
    start = window->DC.CursorPos + padding;
    if (size.y < textSize.y)
        start.y += (textSize.y - size.y) * .5f;
    if (wrapContent)
        start.x += (bbSize.x - imageSize.x) / 2;

    const ImRect image_bb(start, start + size);
    start = window->DC.CursorPos + padding;
    if (!wrapContent)
        start.x += size.x + innerSpacing;
    if (!wrapContent && size.y > textSize.y)
        start.y += (size.y - textSize.y) * .5f;
    ItemSize(bb);
    if (!ItemAdd(bb, id))
        return false;

    // Render
    const ImU32 col = GetColorU32(ImGuiCol_FrameBg);
    RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
    if (bg_col.w > 0.0f)
        window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));

    window->DrawList->AddImage(texId, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));
    //SameLine(size.x+innerSpacing);
    ImVec2 prevPos = window->DC.CursorPos;
    window->DC.CursorPos = start;
    if (wrapContent)
    {
        start.y += size.y - (innerSpacing - (textSize.y / 2));
        start.x += (textSize.x >= bbSize.x ? 0 : bbSize.x - textSize.x - innerSpacing) / 2;
        window->DC.CursorPos = start;
        InputTextEx(label, NULL, buf, (int)buf_size, ImVec2(totalSizeWithoutPadding.x,0), 0);
        start.y = prevPos.y;
        window->DC.CursorPos = start;
        // ImGui::RenderText(start,label);
    }
    else
        InputTextEx(label, NULL, buf, (int)buf_size, ImVec2(0, 0), 0);
    //window->DC.CursorPos = prevPos;
    return true;
}

void ImGui::AlignForWidth(float width, float alignment)
{
    ImGuiStyle &style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
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