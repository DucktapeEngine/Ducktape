cmake_minimum_required(VERSION 3.8)

project("Ducktape")

set(ASSIMP_BUILD_ZLIB ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
# set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)

set(OpenGL_GL_PREFERENCE LEGACY)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Extern/assimp/cmake-modules;${CMAKE_MODULE_PATH}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build") // Fails for reasons: https://github.com/DucktapeEngine/Ducktape/actions/runs/3621178282/jobs/6104292087#step:5:125
# Using manual copying as a temporary work around in Editor's CMakeLists.txt file

if(WIN32)
add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/assimp")
add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/glfw")
endif(WIN32)

add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/imgui")

add_subdirectory("${PROJECT_SOURCE_DIR}/Engine")
set(BUILD_SHARED_LIBS OFF)

add_subdirectory("${PROJECT_SOURCE_DIR}/Editor")

