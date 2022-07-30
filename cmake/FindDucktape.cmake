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

#[=======================================================================[.rst:

Documentation for using find_package() to find the Ducktape library.

#]=======================================================================]

set (Ducktape_FOUND true)
get_filename_component (Ducktape_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# OpenGL
find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
    message ("-- OpenGL found.")
else (OPENGL_FOUND)
    message ("-- OpenGL not found.")
endif ()

set (Ducktape_INCLUDE_DIR 
    ${Ducktape_ROOT_DIR}/engine;
    ${Ducktape_ROOT_DIR}/extern/;
    ${Ducktape_ROOT_DIR}/extern/glm/;
    ${Ducktape_ROOT_DIR}/extern/glfw/include/;
    ${Ducktape_ROOT_DIR}/extern/glad/include/;
    ${Ducktape_ROOT_DIR}/extern/assimp/include;
    ${Ducktape_ROOT_DIR}/build/extern/assimp/include;
    ${Ducktape_ROOT_DIR}/build/extern/glad/include
)

set (Ducktape_LIBRARY_DIR 
    ${Ducktape_ROOT_DIR}/build/engine/;
    ${Ducktape_ROOT_DIR}/build/extern/assimp/bin/;
    ${Ducktape_ROOT_DIR}/build/extern/assimp/contrib/zlib/;
    ${Ducktape_ROOT_DIR}/build/extern/glad/;
    ${Ducktape_ROOT_DIR}/build/extern/glfw/src;
)

set (Ducktape_LIBRARY
    Ducktape
    glfw3
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    glad
)