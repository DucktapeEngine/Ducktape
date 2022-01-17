cmake_minimum_required (VERSION 3.12)

project(helloducktape LANGUAGES CXX)
set(executable_name "helloducktape")

add_executable(helloducktape helloducktape.cpp)

get_filename_component(DTROOT ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)
get_filename_component(DTROOT ${DTROOT}/.. ABSOLUTE)

set(PROJECT helloducktape)
include(${DTROOT}/cmake/ducktape.cmake)