#ifndef H_IMGUI
#define H_IMGUI
    #include <imgui.h>
#endif
#ifndef H_IMGUI_INTERNAL
#define H_IMGUI_INTERNAL
    #include <imgui_internal.h>
#endif
namespace ImGui {
// label is used as id
// <0 frame_padding uses default frame padding settings. 0 for no padding
IMGUI_API bool ImageButtonWithText(ImTextureID texId,const char* label,const ImVec2& imageSize=ImVec2(0,0),bool wrapContent=false, const ImVec2& uv0 = ImVec2(0,0),  const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1));
ImVec2 operator *(ImVec2 &iv2,float fl);
ImVec2 operator *(const ImVec2 &iv2,float fl);
ImVec2 operator*(ImVec2 &iv2,int i);
ImVec2 operator+(ImVec2 &iv2,ImVec2 &otheriv2);
ImVec2 operator+(const ImVec2 &iv2,const ImVec2 &otheriv2);
}