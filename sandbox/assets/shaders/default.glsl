#type vertex;
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

#type fragment;
#version 440 core

out vec4 FragColor;

#define MAX_LIGHT_NO 25

struct Material {
    vec3 color;
    float shininess;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    sampler2D height;
    sampler2D roughness;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool enabled;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool enabled;
};

uniform vec3 viewPos;
uniform PointLight pointLights[MAX_LIGHT_NO];
uniform DirectionalLight directionalLights[MAX_LIGHT_NO];
uniform Material material;

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Combine
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoords)) * material.color;
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)) * material.color;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)) * material.color;
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)) * material.color;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)) * material.color;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)) * material.color;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0);

    // Directional Lights
    for(int i = 0; i < MAX_LIGHT_NO; i++)
        if (directionalLights[i].enabled)
            result += CalculateDirLight(directionalLights[i], norm, viewDir);

    // Point Lights
    for(int i = 0; i < MAX_LIGHT_NO; i++)
        if (pointLights[i].enabled)
            result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);

    // FragColor = vec4(result, 1.0);
    FragColor = texture(material.diffuse, TexCoords);
}