cmake_minimum_required (VERSION 3.12)

project(rendering LANGUAGES CXX)
set(executable_name "rendering")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

add_executable(rendering rendering.cpp)

get_filename_component(DTROOT ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)
get_filename_component(DTROOT ${DTROOT}/.. ABSOLUTE)

set(PROJECT rendering)
include(${DTROOT}/cmake/ducktape.cmake)