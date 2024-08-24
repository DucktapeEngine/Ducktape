set (Ducktape_FOUND true)

# OpenGL
find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
    message ("-- OpenGL found.")
else (OPENGL_FOUND)
    message ("-- OpenGL not found.")
endif ()

set (Ducktape_INCLUDE_DIR 
    ${Ducktape_ROOT_DIR}/Engine;
    ${Ducktape_ROOT_DIR}/Editor;
    ${Ducktape_ROOT_DIR}/Runtime;
    ${Ducktape_ROOT_DIR}/Extern/;
    ${Ducktape_ROOT_DIR}/Extern/glm/;
    ${Ducktape_ROOT_DIR}/Extern/glfw/include/;
    ${Ducktape_ROOT_DIR}/Extern/glad/include/;
    ${Ducktape_ROOT_DIR}/Extern/assimp/include;
    ${Ducktape_ROOT_DIR}/Build/Extern/assimp/include;
    ${Ducktape_ROOT_DIR}/Extern/imgui/backends/;
    ${Ducktape_ROOT_DIR}/Extern/imgui/;
    ${Ducktape_ROOT_DIR}/Extern/json/include/;
)

set (Ducktape_LIBRARY
    glfw
    OpenGL::GL
    glad
    assimp
    imgui
)

if (UNIX)
    set (Ducktape_LIBRARY
	${Ducktape_LIBRARY}
	dl
    )
endif()
