cmake_minimum_required (VERSION 3.8)

project ("Ducktape")

set(ASSIMP_BUILD_ZLIB ON)
set(BUILD_SHARED_LIBS ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/extern/assimp/cmake-modules/;${CMAKE_MODULE_PATH}")
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/assimp")
set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glad")

add_subdirectory("${PROJECT_SOURCE_DIR}/engine/")
add_subdirectory("${PROJECT_SOURCE_DIR}/editor/")
add_subdirectory("${PROJECT_SOURCE_DIR}/resources/scripts/")