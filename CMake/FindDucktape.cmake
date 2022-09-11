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

#[=======================================================================[.rst:

Documentation for using find_package() to find the Ducktape library.

#]=======================================================================]

set (Ducktape_FOUND true)

# OpenGL
find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
    message ("-- OpenGL found.")
else (OPENGL_FOUND)
    message ("-- OpenGL not found.")
endif ()

set (Ducktape_INCLUDE_DIR 
    ${Ducktape_ROOT_DIR}/Engine;
    ${Ducktape_ROOT_DIR}/Extern/;
    ${Ducktape_ROOT_DIR}/Extern/glm/;
    ${Ducktape_ROOT_DIR}/Extern/glfw/include/;
    ${Ducktape_ROOT_DIR}/Extern/glad/include/;
    ${Ducktape_ROOT_DIR}/Extern/entt/single_include;
    ${Ducktape_ROOT_DIR}/Extern/assimp/include;
    ${Ducktape_ROOT_DIR}/Build/Extern/assimp/include;
    ${Ducktape_ROOT_DIR}/Build/Extern/glad/include
)

set (Ducktape_LIBRARY_DIR 
    ${Ducktape_ROOT_DIR}/Build/Engine/;
    ${Ducktape_ROOT_DIR}/Build/Extern/assimp/bin/;
    ${Ducktape_ROOT_DIR}/Build/Extern/assimp/contrib/zlib/;
    ${Ducktape_ROOT_DIR}/Build/Extern/glad/;
    ${Ducktape_ROOT_DIR}/Build/Extern/glfw/src;
)

set (Ducktape_LIBRARY
    Ducktape
    glfw3
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLFW_LIBRARIES}
    glad
    assimp-5
)