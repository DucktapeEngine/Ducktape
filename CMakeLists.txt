# CMakeList.txt : CMake project for Ducktape, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Ducktape")
set(CMAKE_CURRENT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_BUILD_TYPE "DEBUG")
set(CMAKE_CXX_STANDARD 20)

# Ducktape
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE imgui_source_list "${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp")

add_executable (Ducktape
    ${source_list}
    ${imgui_source_list}
)

target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/src/")
target_compile_features(Ducktape PRIVATE cxx_std_17)

# Extern
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/")

# GLM
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glm/")

# EnTT
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/entt/single_include")

# ImGUI
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/imgui/")

# Raylib
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/raylib")
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/raylib/src")
target_link_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/raylib/build/raylib")
target_link_libraries(Ducktape PUBLIC raylib)
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/raylib-cpp/include")