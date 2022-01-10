cmake_minimum_required (VERSION 3.12)

enable_language(C)
set(CMAKE_CXX_FLAGS "-fPIC")

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include")

target_link_directories(${PROJECT} PUBLIC "${DTROOT}/build")

target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/box2d/include/;${DTROOT}/include/Ducktape/external/box2d/src;")

target_link_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/box2d/bin;")

if (UNIX)
    target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/include")

    target_link_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib;")
endif (UNIX)

if (WIN32)
    target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/include")

    target_link_directories(${PROJECT} PUBLIC "${DTROOT}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib;")
endif (WIN32)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${DTROOT}/include/Ducktape/external/)

if (UNIX)
    find_package(SFML PATHS ${DTROOT}/include/Ducktape/external/SFML-linux-gcc/lib/cmake/SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

    target_link_libraries(${PROJECT} PRIVATE ${DTROOT}/include/Ducktape/external/box2d/bin/libbox2d.a)
endif (UNIX)

if (WIN32)
    find_package(SFML PATHS ${DTROOT}/include/Ducktape/external/SFML-windows-gcc/SFML-2.5.1/lib/cmake/SFML COMPONENTS graphics audio window network system CONFIG REQUIRED)

    target_link_libraries(${PROJECT} PRIVATE ${DTROOT}/include/Ducktape/external/box2d/bin/box2d.lib)
endif (WIN32)

target_link_libraries(${PROJECT} PRIVATE ducktape sfml-graphics sfml-window sfml-audio sfml-network sfml-system box2d glad glfw imgui sajson)