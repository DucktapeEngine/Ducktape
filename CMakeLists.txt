cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape")

if (UNIX)
    message (STATUS "Platform Detected: Linux")
endif (UNIX)

if (WIN32)
    message (STATUS "Platform Detected: Windows")
endif (WIN32)

project(ducktape LANGUAGES CXX)
enable_language(C)

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/Ducktape/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/Ducktape/*.cpp")

file(GLOB_RECURSE header_list "${PROJECT_SOURCE_DIR}/include/Ducktape/**/*.h" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h")

add_library(ducktape ${source_list} ${header_list})

set_target_properties(ducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

set(CMAKE_CXX_FLAGS "-pthread -fPIC")

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include;${PROJECT_SOURCE_DIR}/src;")

# Box2D
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/box2d)
target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/box2d/include")
target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/build/extern/box2d/bin")

# SFML
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/SFML)
set(SFML_DIR ${PROJECT_SOURCE_DIR}/extern/SFML/cmake/)

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/SFML/include")
target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/build/extern/SFML/lib")

target_link_libraries(ducktape PRIVATE 
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-network
    glad
    glfw
    imgui
    sajson
    box2d
)

add_subdirectory(${PROJECT_SOURCE_DIR}/dev)