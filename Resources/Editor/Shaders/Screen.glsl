#ifdef DT_SHADER_FRAG
    in vec2 TexCoords;

    uniform sampler2D screenTexture;

    vec4 Frag()
    {
        vec3 col = texture(screenTexture, TexCoords).rgb;
        return vec4(col, 1.0);
    }
#endif

#ifdef DT_SHADER_VERT
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTexCoords;

    out vec2 TexCoords;

    vec4 Vert()
    {
        TexCoords = aTexCoords;
        return vec4(aPos.x, aPos.y, 0.0, 1.0); 
    }
#endif

DT_REGISTER_SHADER();