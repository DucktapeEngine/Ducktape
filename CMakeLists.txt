# CMakeList.txt : CMake project for Ducktape, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Ducktape")
set(CMAKE_CURRENT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_BUILD_TYPE "DEBUG")
set(CMAKE_CXX_STANDARD 20)

# Ducktape
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(glad_source_list "${PROJECT_SOURCE_DIR}/extern/glad/src/glad.c" "${PROJECT_SOURCE_DIR}/extern/glad/include/glad/glad.h")
file(GLOB_RECURSE imgui_source_list "${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp")

set(CMAKE_CXX_FLAGS "-fPIC")

add_executable (Ducktape
    ${source_list}
    ${glad_source_list}
    ${imgui_source_list}
)

set_target_properties(Ducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/src/")
target_compile_features(Ducktape PRIVATE cxx_std_17)

# Extern
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/")

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("OpenGL found.")
else (OPENGL_FOUND)
    message("OpenGL not found.")
endif()
target_link_libraries(Ducktape PUBLIC ${OPENGL_gl_LIBRARY})

# GLM
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glm/")

# EnTT
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/entt/single_include")

# ImGUI
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/imgui/")

# GLFW
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glfw")
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glfw/include")
target_link_libraries(Ducktape PUBLIC glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

# GLAD
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glad/include/")

# Assimp
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/extern/assimp/cmake-modules/;${CMAKE_MODULE_PATH}")

find_package(assimp REQUIRED)
target_link_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/extern/assimp/lib)
target_link_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/extern/assimp/contrib/zlib)
target_include_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/extern/assimp/include)
target_include_directories(Ducktape PUBLIC ${PROJECT_SOURCE_DIR}/build/extern/assimp/include/)
target_link_libraries (Ducktape PUBLIC assimp)