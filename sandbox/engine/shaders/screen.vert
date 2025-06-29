#version 440 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

vec4 Vert()
{
    TexCoords = aTexCoords;
    return vec4(aPos.x, aPos.y, 0.0, 1.0); 
}

void main()
{
    gl_Position = Vert();
}