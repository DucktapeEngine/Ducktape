#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec4 Vert()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // TODO: Calculate this on CPU for inverse() is a heavy operation
    TexCoords = aTexCoords;

    return projection * view * vec4(FragPos, 1.0);
}

void main()
{
    gl_Position = Vert();
}