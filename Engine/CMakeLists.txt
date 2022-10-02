# Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
# Copyright (C) 2022 Aryan Baburajan
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# In case of any further questions feel free to contact me at
# the following email address:
# aryanbaburajan2007@gmail.com

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

# Ducktape
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/Engine/**/*.cpp" "${PROJECT_SOURCE_DIR}/Engine/*.cpp")

set(CMAKE_CXX_FLAGS "-fPIC")

add_library(Ducktape
    ${source_list}
)

set_target_properties(Ducktape PROPERTIES
    CXX_EXTENSIONS OFF
)

target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Engine/")
target_compile_features(Ducktape PRIVATE cxx_std_17)

# Dependencies
find_package(OpenGL REQUIRED)

if(OPENGL_FOUND)
    message("-- OpenGL found.")
else(OPENGL_FOUND)
    message("-- OpenGL not found.")
endif()

target_include_directories(Ducktape PUBLIC
    ${PROJECT_SOURCE_DIR}/Engine;
    ${PROJECT_SOURCE_DIR}/Extern/;
    ${PROJECT_SOURCE_DIR}/Extern/glm/;
    ${PROJECT_SOURCE_DIR}/Extern/glfw/include/;
    ${PROJECT_SOURCE_DIR}/Extern/glad/include/;
    ${PROJECT_SOURCE_DIR}/Extern/entt/single_include;
    ${PROJECT_SOURCE_DIR}/Extern/assimp/include;
    ${PROJECT_SOURCE_DIR}/Build/Extern/assimp/include;
    ${PROJECT_SOURCE_DIR}/Extern/imgui/backends/;
    ${PROJECT_SOURCE_DIR}/Extern/imgui/;
)

target_link_directories(Ducktape PUBLIC
    ${PROJECT_SOURCE_DIR}/Build/Engine/;
    ${PROJECT_SOURCE_DIR}/Build/Extern/assimp/bin/;
    ${PROJECT_SOURCE_DIR}/Build/Extern/assimp/contrib/zlib/;
    ${PROJECT_SOURCE_DIR}/Build/Extern/glad/;
    ${PROJECT_SOURCE_DIR}/Build/Extern/glfw/src;
    ${PROJECT_SOURCE_DIR}/Build/Extern/imgui;
)

target_link_libraries(Ducktape PUBLIC
    glfw
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    glad
    assimp
    imgui
)
