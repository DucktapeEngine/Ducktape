# Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
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

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

# Editor
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/editor/**/*.cpp" "${PROJECT_SOURCE_DIR}/editor/*.cpp")
set(imgui_source_list
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_demo.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_draw.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_tables.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_widgets.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/misc/cpp/imgui_stdlib.cpp"
)

set(CMAKE_CXX_FLAGS "-fPIC")

add_executable (Editor
    ${source_list}
    ${imgui_source_list}
)

set_target_properties (Editor PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_compile_features (Editor PRIVATE cxx_std_17)

target_include_directories(Editor PUBLIC "${PROJECT_SOURCE_DIR}/editor")

# Ducktape
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
set(TARGET Editor)
find_package (Ducktape REQUIRED)

if (Ducktape_FOUND)
    message ("-- Ducktape found.")
else (Ducktape_FOUND)
    message ("-- Ducktape not found.")
endif ()

target_include_directories (Editor PUBLIC ${Ducktape_INCLUDE_DIR})
target_link_directories (Editor PUBLIC ${Ducktape_LIBRARY_DIR})
target_link_libraries (Editor PUBLIC ${Ducktape_LIBRARY})

message (${Ducktape_LIBRARY_DIR})

target_include_directories (Editor PUBLIC "${PROJECT_SOURCE_DIR}/extern/imgui/;${PROJECT_SOURCE_DIR}/extern/imgui/backends/")