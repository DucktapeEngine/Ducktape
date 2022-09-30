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

# Scripts
set(CMAKE_CXX_FLAGS "-fPIC")

# Ducktape
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")
set(Ducktape_ROOT_DIR "${PROJECT_SOURCE_DIR}")
find_package (Ducktape REQUIRED)

if (Ducktape_FOUND)
    message ("-- Ducktape found.")
else (Ducktape_FOUND)
    message ("-- Ducktape not found.")
endif ()

include_directories (${Ducktape_INCLUDE_DIR})
link_directories (${Ducktape_LIBRARY_DIR})
link_libraries (${Ducktape_LIBRARY})

add_library (Game SHARED "${PROJECT_SOURCE_DIR}/Resources/Scripts/PlayerController.cpp")