cmake_minimum_required (VERSION 3.12)

enable_language(C)
set(CMAKE_CXX_FLAGS "-fPIC")

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include")
target_link_directories(${PROJECT} PUBLIC "${DTROOT}/build")

# Box2D
add_subdirectory(${DTROOT}/extern/box2d ${DTROOT}/build/extern/box2d/bin)
target_include_directories(${PROJECT} PUBLIC "${DTROOT}/extern/box2d/include")
target_link_directories(${PROJECT} PUBLIC "${DTROOT}/build/extern/box2d/bin")

# SFML
add_subdirectory(${DTROOT}/extern/SFML ${DTROOT}/build/extern/SFML/lib)
set(SFML_DIR ${DTROOT}/extern/SFML/cmake/)

target_include_directories(${PROJECT} PUBLIC "${DTROOT}/extern/SFML/include")
target_link_directories(${PROJECT} PUBLIC "${DTROOT}/build/extern/SFML/lib")

target_link_libraries(${PROJECT} PRIVATE
    ducktape
    sfml-window
    sfml-system
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-network
    glad
    glfw
    imgui
    sajson
    box2d
)