cmake_minimum_required (VERSION 3.12)

project(dev LANGUAGES CXX)
set(executable_name "dev")

add_executable(dev dev.cpp)

get_filename_component(DTROOT ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)

set(PROJECT dev)
include(${DTROOT}/cmake/ducktape.cmake)