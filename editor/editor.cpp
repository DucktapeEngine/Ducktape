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

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "core/log.h"
#include "core/window.h"
#include "editor.h"
#include "renderer/renderer.h"

namespace dt {
// todo: use references over pointers
// todo: use const appropriately
editor_t::editor_t(const window_t &window) {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDragClickToInputText = true;

    ImGui_ImplGlfw_InitForOpenGL(window.handle, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    io.Fonts->AddFontFromFileTTF("./assets/engine/fonts/Funnel_Display/static/FunnelDisplay-SemiBold.ttf", 15.f);

    setup_ImGui_style();
    glfwMaximizeWindow(window.handle);

    LOG("editor constructed");
}

editor_t::~editor_t() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void editor_t::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void editor_t::end_frame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void editor_t::start(context_t *ctx) {
    for (std::shared_ptr<panel_base> panel : panels)
        panel->start(ctx);
}

void editor_t::draw(context_t *ctx, float dt) {
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode;
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    dockspace_id = ImGui::GetID("MyDockspace");

    ImGui::DockSpaceOverViewport(dockspace_id, viewport, dockspace_flags);

    for (std::shared_ptr<panel_base> panel : panels)
        panel->draw(ctx, dt);
}

void editor_t::setup_ImGui_style() {
    ImGuiStyle &style = ImGui::GetStyle();

    style.Alpha = 1.f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(10.f, 10.f);
    style.WindowRounding = 0.f;
    style.WindowBorderSize = 1.f;
    style.WindowMinSize = ImVec2(32.f, 32.f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding = 6.f;
    style.ChildBorderSize = 1.f;
    style.PopupRounding = 6.f;
    style.PopupBorderSize = 1.f;
    style.FramePadding = ImVec2(8.f, 6.f);
    style.FrameRounding = 6.f;
    style.FrameBorderSize = 1.f;
    style.ItemSpacing = ImVec2(6.f, 6.f);
    style.ItemInnerSpacing = ImVec2(4.f, 4.f);
    style.CellPadding = ImVec2(4.f, 2.f);
    style.IndentSpacing = 11.f;
    style.ColumnsMinSpacing = 6.f;
    style.ScrollbarSize = 14.f;
    style.ScrollbarRounding = 6.f;
    style.GrabMinSize = 10.f;
    style.GrabRounding = 6.f;
    style.TabRounding = 6.f;
    style.TabBorderSize = 1.f;
    style.TabCloseButtonMinWidthSelected = 0.f;
    style.TabCloseButtonMinWidthUnselected = 0.f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.f, 0.f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.f, 1.f, 1.f, 0.05999999865889549f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.f, 0.4666666686534882f, 0.7843137383460999f, 1.f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.f, 1.f, 1.f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.f);
}
} // namespace dt