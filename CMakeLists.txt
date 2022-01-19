cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape")

if (UNIX)
    message (STATUS "Platform Detected: Linux")
endif (UNIX)

if (WIN32)
    message (STATUS "Platform Detected: Windows")
endif (WIN32)

project(libducktape LANGUAGES CXX)
enable_language(C)

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/Ducktape/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/Ducktape/*.cpp")

file(GLOB_RECURSE header_list "${PROJECT_SOURCE_DIR}/include/Ducktape/**/*.h" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h")

add_library(libducktape ${source_list} ${header_list})

set_target_properties(libducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

set(CMAKE_CXX_FLAGS "-g -pthread -fPIC")

target_include_directories(libducktape PUBLIC "${PROJECT_SOURCE_DIR}/include;${PROJECT_SOURCE_DIR}/src;")

target_link_directories(libducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/box2d/bin")

if (UNIX)
    set(SFML_DIR ${PROJECT_SOURCE_DIR}/extern/SFML-linux-gcc/SFML-2.5.1/lib/cmake/SFML)

    target_link_directories(libducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/SFML-linux-gcc/SFML-2.5.1/lib")
endif (UNIX)

if (WIN32)
    set(SFML_DIR ${PROJECT_SOURCE_DIR}/extern/SFML-windows-gcc/SFML-2.5.1/lib/cmake/SFML)

    target_link_directories(libducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/SFML-windows-gcc/SFML-2.5.1/lib")
endif (WIN32)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/extern/)

find_package(SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

target_link_libraries(libducktape PRIVATE 
    sfml-window-s
    sfml-system-s
    opengl32
    winmm
    gdi32
    sfml-graphics-s
    freetype
    sfml-audio-s
    openal32
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    sfml-network-s
    ws2_32
    box2d
)

if(WIN32)
    set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR})
    string(REPLACE "/" "\\" PROJECT_SRC_DIR ${PROJECT_SRC_DIR}) # replace / with \ for windows-like paths
    add_custom_command(TARGET libducktape
        POST_BUILD
        COMMAND ${PROJECT_SRC_DIR}\\utils\\combine.bat
    )
endif()