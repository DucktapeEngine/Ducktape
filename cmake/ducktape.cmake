cmake_minimum_required (VERSION 3.12)

enable_language(C)
set(CMAKE_CXX_FLAGS "-fPIC")

set_target_properties(${PROJECT} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT} PUBLIC "${DTROOT}/include")
target_link_directories(${PROJECT} PUBLIC "${DTROOT}/build")

target_link_libraries(${PROJECT} PUBLIC 
    ducktape
)