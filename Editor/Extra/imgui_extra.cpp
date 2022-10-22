#include <Extra/imgui_extra.h>

namespace ImGui {
    bool ImageButtonWithText(ImTextureID texId,const char* label,const ImVec2& imageSize,bool wrapContent, const ImVec2 &uv0, const ImVec2 &uv1, int frame_padding, const ImVec4 &bg_col, const ImVec4 &tint_col) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
        return false;

        ImVec2 size = imageSize;
        if (size.x<=0 && size.y<=0) {size.x=size.y=ImGui::GetTextLineHeightWithSpacing();}
        else {
            if (size.x<=0)          size.x=size.y;
            else if (size.y<=0)     size.y=size.x;
            size=size * window->FontWindowScale*ImGui::GetIO().FontGlobalScale;
        }

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 textSize = ImGui::CalcTextSize(label,NULL,true);
        const bool hasText = textSize.x>0;
        float fillX = GetContentRegionAvail().x;
        float fillY = size.y + textSize.y;

        const float innerSpacing = hasText ? ((frame_padding >= 0) ? (float)frame_padding : (style.ItemInnerSpacing.x)) : 0.f;
        ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
        ImVec2 totalSizeWithoutPadding(wrapContent?size.x+innerSpacing+imageSize.x:fillX,wrapContent?fillY:size.y>textSize.y ? size.y : textSize.y);
        ImRect bb(window->DC.CursorPos, window->DC.CursorPos + totalSizeWithoutPadding + padding*2);
        ImVec2 bbSize = bb.GetSize();
        ImVec2 start(0,0);
        start = window->DC.CursorPos + padding;
        if (size.y<textSize.y) start.y+=(textSize.y-size.y)*.5f;
        if (wrapContent) start.x += (bbSize.x-imageSize.x)/2;
        
        const ImRect image_bb(start, start + size);
        start = window->DC.CursorPos + padding;
        if (!wrapContent) start.x+=size.x+innerSpacing;
        if (!wrapContent && size.y>textSize.y) 
            start.y+=(size.y-textSize.y)*.5f;
        ItemSize(bb);
        if (!ItemAdd(bb, id))
        return false;

        bool hovered=false, held=false;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held);

        // Render
        const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
        if (bg_col.w > 0.0f)
        window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));

        window->DrawList->AddImage(texId, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));
        
        if (textSize.x>0) 
        {
            if(wrapContent)
            {
                start.y+=size.y - (innerSpacing-(textSize.y/2));
                start.x+=(textSize.x>=bbSize.x?0:bbSize.x-textSize.x-innerSpacing)/2;
                float ellipsisPadding=10.0f;
                //ImGui::RenderTextClipped()
                float ellipsis_max_x=(start+totalSizeWithoutPadding).x+ellipsisPadding;
                ImGui::RenderTextEllipsis(window->DrawList,start,start+totalSizeWithoutPadding,ellipsis_max_x,ellipsis_max_x,label,NULL,NULL);
                //ImGui::RenderText(start,label);
            }  
            else ImGui::RenderText(start,label);
        }
        return pressed;
    }
    ImVec2 operator *(ImVec2 &iv2,float fl)
    {
        return {iv2.x * fl,iv2.y * fl};
    }
    ImVec2 operator *(const ImVec2 &iv2,float fl)
    {
        return {iv2.x * fl,iv2.y * fl};
    }
    ImVec2 operator*(ImVec2 &iv2,int i)
    {
        return {iv2.x * i,iv2.y * i};
    }
    ImVec2 operator+(ImVec2 &iv2,ImVec2 &otheriv2)
    {
        return {iv2.x + otheriv2.x,iv2.y + otheriv2.y};
    }
    ImVec2 operator+(const ImVec2 &iv2,const ImVec2 &otheriv2)
    {
        return {iv2.x + otheriv2.x,iv2.y + otheriv2.y};
    }
} // namespace ImGui