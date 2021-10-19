cmake_minimum_required (VERSION 3.12)

message (STATUS "Building Ducktape .. ")
project(Ducktape LANGUAGES CXX)
set(executable_name "Ducktape")

set(CMAKE_BUILD_TYPE "Debug")

file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/include/Ducktape/*.cpp" "${PROJECT_SOURCE_DIR}/include/Ducktape/*.h")
add_executable(ducktape  ${source_list} ${PROJECT_SOURCE_DIR}/src/main.cpp)
set_target_properties(ducktape PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF)

target_include_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/Ducktape/;${PROJECT_SOURCE_DIR}")
target_link_directories(ducktape PUBLIC "${PROJECT_SOURCE_DIR}/include/box2d/build/bin")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/include/SFML-linux-gcc/lib/cmake/)
find_package(SFML 2.5.1 COMPONENTS graphics audio window network system CONFIG  REQUIRED)
target_link_libraries(ducktape PRIVATE sfml-graphics sfml-window sfml-audio sfml-network sfml-system -lbox2d -lglad -lglfw -limgui -lsajson)
