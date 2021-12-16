cmake_minimum_required (VERSION 3.12)

message(STATUS "Building Flappy Bird ...")
project(flappybird LANGUAGES CXX)
set(executable_name "flappybird")

add_executable(flappybird flappybird.cpp)

get_filename_component(DTROOT ${PROJECT_SOURCE_DIR}/.. ABSOLUTE)
get_filename_component(DTROOT ${DTROOT}/.. ABSOLUTE)

set(CMAKE_CXX_FLAGS "-g")

set(DTROOT ${DTROOT})
set(PROJECT flappybird)
include(${DTROOT}/cmake/ducktape.cmake)