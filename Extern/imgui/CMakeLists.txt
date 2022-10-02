cmake_minimum_required (VERSION 3.8)

add_library(imgui 
    "${PROJECT_SOURCE_DIR}/Extern/imgui/imgui.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/imgui_demo.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/imgui_draw.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/imgui_tables.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/imgui_widgets.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/backends/imgui_impl_glfw.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/backends/imgui_impl_opengl3.cpp"
    "${PROJECT_SOURCE_DIR}/Extern/imgui/misc/cpp/imgui_stdlib.cpp"
)

target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/Extern/imgui")
target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/Extern/glfw/include/")

target_link_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/Build/Extern/glfw/src")
target_link_libraries(imgui PUBLIC glfw)
