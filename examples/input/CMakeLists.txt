cmake_minimum_required (VERSION 3.12)

project(input LANGUAGES CXX)
set(executable_name "input")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

add_executable(input input.cpp)

get_filename_component(DTROOT ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)
get_filename_component(DTROOT ${DTROOT}/.. ABSOLUTE)

set(PROJECT input)
include(${DTROOT}/cmake/ducktape.cmake)