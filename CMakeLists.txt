cmake_minimum_required(VERSION 3.8)

project("Ducktape")

set(ASSIMP_BUILD_ZLIB ON)
set(BUILD_SHARED_LIBS ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Extern/assimp/cmake-modules/;${CMAKE_MODULE_PATH}")
set(OpenGL_GL_PREFERENCE LEGACY)

if(WIN32)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/assimp")
    add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/glfw")
endif(WIN32)

add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/glad")
add_subdirectory("${PROJECT_SOURCE_DIR}/Extern/imgui")

set(BUILD_SHARED_LIBS OFF)

add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/")
add_subdirectory("${PROJECT_SOURCE_DIR}/Editor/")
add_subdirectory("${PROJECT_SOURCE_DIR}/Resources/Scripts/")
