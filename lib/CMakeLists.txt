
if(WIN32)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/assimp")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glfw")
endif(WIN32)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/fmt")

add_library(imgui 
    "${PROJECT_SOURCE_DIR}/lib/imgui/imgui.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/imgui_demo.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/imgui_draw.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/imgui_tables.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imgui/misc/cpp/imgui_stdlib.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imguizmo/GraphEditor.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imguizmo/ImCurveEdit.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imguizmo/ImGradient.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imguizmo/ImGuizmo.cpp"
    "${PROJECT_SOURCE_DIR}/lib/imguizmo/ImSequencer.cpp"
)

target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/lib/imgui")
target_link_libraries(imgui PUBLIC glfw)