cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape")

if (UNIX)
    message (STATUS "Platform Detected: Linux")
    set(CMAKE_CXX_FLAGS "-g -pthread -fPIC")
endif (UNIX)

if (WIN32)
    message (STATUS "Platform Detected: Windows")
    set(CMAKE_CXX_FLAGS "-g -pthread")
endif (WIN32)

project(Ducktape) #executable name set by the project name
enable_language(C)

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/Ducktape/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/Ducktape/*.cpp")
file(GLOB_RECURSE header_list "${PROJECT_SOURCE_DIR}/include/Ducktape/**/*.h" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h")

add_library(ducktape ${source_list} ${header_list})

set_target_properties(ducktape PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

set(EXTERNAL include/Ducktape/external)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${EXTERNAL})
set(BOX2D_BIN ${EXTERNAL}/box2d/bin)
set(SFML_BIN ${EXTERNAL}/SFML/bin)

add_subdirectory(${EXTERNAL}/box2d ${BOX2D_BIN})
add_subdirectory(${EXTERNAL}/SFML ${SFML_BIN})

#find_package(SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

target_include_directories(
    ducktape PUBLIC
    include
    ${EXTERNAL}/box2d/include
    ${EXTERNAL}/SFML/include
)
target_link_libraries(
    ducktape PUBLIC
    ${BOX2D_BIN}
    ${SFML_BIN}
)
target_link_libraries(ducktape PUBLIC sfml-graphics sfml-window sfml-audio sfml-network sfml-system box2d)