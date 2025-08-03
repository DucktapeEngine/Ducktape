set(Ducktape_FOUND true)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message ("-- OpenGL found.")
else(OPENGL_FOUND)
    message ("-- OpenGL not found.")
endif()

set(Ducktape_INCLUDE_DIR
    ${Ducktape_ROOT_DIR}/engine;
    ${Ducktape_ROOT_DIR}/editor;
    ${Ducktape_ROOT_DIR}/runtime;
    ${Ducktape_ROOT_DIR}/lib/;
    ${Ducktape_ROOT_DIR}/lib/glm/;
    ${Ducktape_ROOT_DIR}/lib/glfw/include/;
    ${Ducktape_ROOT_DIR}/lib/glad/include/;
    ${Ducktape_ROOT_DIR}/lib/assimp/include;
    ${Ducktape_ROOT_DIR}/build/lib/assimp/include;
    ${Ducktape_ROOT_DIR}/lib/json/include/;
    ${Ducktape_ROOT_DIR}/lib/fmt/include/;
    ${Ducktape_ROOT_DIR}/lib/entt/single_include/;
    ${Ducktape_ROOT_DIR}/lib/tracy/public/;
)

set(Ducktape_LIBRARY
    assimp
    fmt
    glfw
    glad
    imgui
    OpenGL::GL
    Tracy::TracyClient
)

if(UNIX)
    set(Ducktape_LIBRARY ${Ducktape_LIBRARY} dl)
endif()
