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

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

# DucktapeEditor
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/Editor/**/*.cpp" "${PROJECT_SOURCE_DIR}/Editor/*.cpp")

set(CMAKE_CXX_FLAGS "-fPIC")

add_executable (DucktapeEditor
    ${source_list}
)

set_target_properties (DucktapeEditor PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_compile_features (DucktapeEditor PRIVATE cxx_std_17)

target_include_directories(DucktapeEditor PUBLIC "${PROJECT_SOURCE_DIR}/Editor")

# Ducktape
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")
set(TARGET DucktapeEditor)
set(Ducktape_ROOT_DIR "${PROJECT_SOURCE_DIR}")
find_package (Ducktape REQUIRED)

if (Ducktape_FOUND)
    message ("-- Ducktape found.")
else (Ducktape_FOUND)
    message ("-- Ducktape not found.")
endif ()

target_include_directories (DucktapeEditor PUBLIC ${Ducktape_INCLUDE_DIR})
target_link_libraries (DucktapeEditor PUBLIC ${Ducktape_LIBRARY})