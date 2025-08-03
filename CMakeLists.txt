# MIT License

# Copyright(c) 2021 - 2025 Aryan Baburajan

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files(the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.16)

project("Ducktape" VERSION 1.0.0)

set(BUILD_SHARED_LIBS ON)
set(ASSIMP_BUILD_ZLIB ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(ASSIMP_BUILD_ALL_EXPORTER_BY_DEFAULT OFF)
set(OpenGL_GL_PREFERENCE LEGACY)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

option(DT_EDITOR "Build the editor." OFF)
set(DT_EDITOR ON)

message(STATUS "DT_EDITOR ${DT_EDITOR}")

if(DT_EDITOR)
    add_compile_definitions(DT_EDITOR)
    message(STATUS "Compiling the editor.")
else()
    message(STATUS "Exporting your project.")
endif()

# set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/extern/assimp/cmake-modules;${CMAKE_MODULE_PATH}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
set(Ducktape_ROOT_DIR "${PROJECT_SOURCE_DIR}")
find_package(Ducktape REQUIRED)

if(Ducktape_FOUND)
    message(STATUS "Ducktape found.")
else(Ducktape_FOUND)
    message(STATUS "Ducktape not found.")
endif()

include_directories(${Ducktape_INCLUDE_DIR})
link_directories(${Ducktape_LIBRARY_DIR})
link_libraries(${Ducktape_LIBRARY})

add_subdirectory("${PROJECT_SOURCE_DIR}/engine")
if (DT_EDITOR)
    add_subdirectory("${PROJECT_SOURCE_DIR}/editor")
endif()
add_subdirectory("${PROJECT_SOURCE_DIR}/runtime")
add_subdirectory("${PROJECT_SOURCE_DIR}/sandbox")