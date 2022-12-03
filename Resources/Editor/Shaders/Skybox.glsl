#ifdef DT_SHADER_FRAG
    in vec3 TexCoords;

    uniform samplerCube skybox;

    vec4 Frag()
    {
        return texture(skybox, TexCoords);
    }
#endif

#ifdef DT_SHADER_VERT
    layout (location = 0) in vec3 aPos;

    out vec3 TexCoords;

    uniform mat4 projection;
    uniform mat4 view;

    vec4 Vert()
    {
        TexCoords = aPos;
        return projection * view * vec4(aPos, 1.0);
    }
#endif

DT_REGISTER_SHADER();