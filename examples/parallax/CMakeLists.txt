cmake_minimum_required (VERSION 3.12)

project(parallax LANGUAGES CXX)
set(executable_name "parallax")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

add_executable(parallax parallax.cpp)

get_filename_component(DTROOT ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)
get_filename_component(DTROOT ${DTROOT}/.. ABSOLUTE)

set(PROJECT parallax)
include(${DTROOT}/cmake/ducktape.cmake)