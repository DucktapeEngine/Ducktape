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

# Ducktape
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/Engine/**/*.cpp" "${PROJECT_SOURCE_DIR}/Engine/*.cpp")

set(CMAKE_CXX_FLAGS "-fPIC")

add_library (Ducktape
    ${source_list}
)

set_target_properties(Ducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Engine/")
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Resources/Scripts/")
target_compile_features(Ducktape PRIVATE cxx_std_17)

# Extern
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Extern/")

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("-- OpenGL found.")
else (OPENGL_FOUND)
    message("-- OpenGL not found.")
endif()
target_link_libraries(Ducktape PUBLIC ${OPENGL_gl_LIBRARY})

# GLM
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Extern/glm/")

# EnTT
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Extern/entt/single_include")

# GLFW
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Extern/glfw/include")
target_link_libraries(Ducktape PUBLIC glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

# GLAD
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/Extern/glad/include/")
target_link_libraries(Ducktape PUBLIC glad)

# Assimp
target_link_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/Extern/assimp/bin)
target_link_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/Extern/assimp/contrib/zlib)
target_include_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/Extern/assimp/include)
target_include_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/Extern/assimp/include/)
target_link_libraries(Ducktape PUBLIC assimp zlibstatic)