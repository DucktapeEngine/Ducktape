cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape ...")
project(ducktape LANGUAGES CXX)
set(executable_name "Ducktape")
enable_language(C)

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/Ducktape/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/Ducktape/*.cpp")

file(GLOB_RECURSE header_list "${PROJECT_SOURCE_DIR}/include/Ducktape/**/*.h" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h")

add_library(ducktape ${source_list} ${header_list})

set_target_properties(ducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

set(CMAKE_CXX_FLAGS "-std=c++17 -g -fPIC")

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include;${PROJECT_SOURCE_DIR}/include/Ducktape;${PROJECT_SOURCE_DIR}/include/Ducktape/audio;${PROJECT_SOURCE_DIR}/include/Ducktape/engine;${PROJECT_SOURCE_DIR}/include/Ducktape/physics;${PROJECT_SOURCE_DIR}/include/Ducktape/rendering;")

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/src/Ducktape;${PROJECT_SOURCE_DIR}/src/Ducktape/audio;${PROJECT_SOURCE_DIR}/src/Ducktape/engine;${PROJECT_SOURCE_DIR}/src/Ducktape/physics;${PROJECT_SOURCE_DIR}/src/Ducktape/rendering;")

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/box2d/include/;${PROJECT_SOURCE_DIR}/include/Ducktape/external/box2d/src;")

target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/box2d/bin;")

if (UNIX)
    target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/include")

    target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib;")
endif (UNIX)

if (WIN32)
    target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/include")

    target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib;")
endif (WIN32)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/include/Ducktape/external/)

if (UNIX)
    find_package(SFML PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/Ducktape/external/SFML-linux-gcc/lib/cmake/SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

    target_link_libraries(ducktape PRIVATE ${PROJECT_SOURCE_DIR}/include/Ducktape/external/box2d/bin/libbox2d.a)
endif (UNIX)

if (WIN32)
    find_package(SFML PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib/cmake/SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

    target_link_libraries(ducktape PRIVATE ${PROJECT_SOURCE_DIR}/include/Ducktape/external/box2d/bin/box2d.lib)
endif (WIN32)

target_link_libraries(ducktape PRIVATE sfml-graphics sfml-window sfml-audio sfml-network sfml-system -lglad -lglfw -limgui -lsajson)