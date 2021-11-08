set(CMAKE_GENERATOR "Unix Makefiles")
cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape .. ")
project(Ducktape LANGUAGES CXX)
set(executable_name "Ducktape")
enable_language(C)

if (WIN32)
    set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
endif (WIN32)

if (UNIX)
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif (UNIX)

set(CMAKE_CXX_COMPILER_ID "GNU")

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/include/Ducktape/*.cpp" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h" "${PROJECT_SOURCE_DIR}/include/box2d/src/*.cpp")

add_executable(ducktape  ${source_list} ${PROJECT_SOURCE_DIR}/examples/flappybird.cpp)

set_target_properties(ducktape PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-g -pthread")

if (UNIX)
    target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/;${PROJECT_SOURCE_DIR};${PROJECT_SOURCE_DIR}/include/box2d/include/;${PROJECT_SOURCE_DIR}/include/box2d/src;${PROJECT_SOURCE_DIR}/include/SFML-linux-gcc/include")

    target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/box2d/bin;${PROJECT_SOURCE_DIR}/include/SFML-linux-gcc/SFML-2.5.1/lib/;")
endif (UNIX)

if (WIN32)
    target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/;${PROJECT_SOURCE_DIR};${PROJECT_SOURCE_DIR}/include/box2d/include/;${PROJECT_SOURCE_DIR}/include/box2d/src;${PROJECT_SOURCE_DIR}/include/SFML-windows-gcc/SFML-2.5.1/include")

    target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/box2d/bin;${PROJECT_SOURCE_DIR}/include/SFML-linux-gcc/SFML-2.5.1/lib/;${PROJECT_SOURCE_DIR}/include/SFML-windows-gcc/SFML-2.5.1/lib")
endif (WIN32)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/include/)

find_package(SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

target_link_libraries(ducktape PRIVATE sfml-graphics sfml-window sfml-audio sfml-network sfml-system -lbox2d -lglad -lglfw -limgui -lsajson)