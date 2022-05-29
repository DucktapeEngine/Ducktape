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
file(GLOB_RECURSE imgui_source_list "${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp")

set(CMAKE_CXX_FLAGS "-fPIC")

add_executable (Ducktape
    ${source_list}
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

# GLM
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glm/")

# EnTT
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/entt/single_include")

# ImGUI
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/imgui/")

# SFML
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARY TRUE)
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/SFML)
set(SFML_DIR ${PROJECT_SOURCE_DIR}/extern/SFML/cmake/)

target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/SFML/include")
target_link_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/build/extern/SFML/lib")

target_link_libraries(Ducktape PRIVATE
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-network
)