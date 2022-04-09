# CMakeList.txt : CMake project for Ducktape, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Ducktape")
set(CMAKE_CURRENT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build/")

# Ducktape
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/**/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable (Ducktape 
    ${source_list}
)
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/src/")
target_compile_features(Ducktape PRIVATE cxx_std_17)

# Extern
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/")

# Vulkan
find_package(Vulkan)

if (${Vulkan_FOUND})
    message (STATUS "Found Vulkan")
    target_link_libraries(Ducktape PRIVATE Vulkan::Vulkan)
else (${GTK_FOUND})
    message (FATAL_ERROR "Vulkan SDK has not been installed. Please install Vulkan SDK and try again.")
endif()

# GLFW
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glfw")
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glfw/include")
target_link_libraries(Ducktape PUBLIC glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

# GLM
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/glm/")

# EnTT
target_include_directories(Ducktape PUBLIC "${PROJECT_SOURCE_DIR}/extern/entt/single_include")