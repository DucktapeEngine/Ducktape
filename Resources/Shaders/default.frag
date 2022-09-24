#version 330 core

#define MAX_LIGHT_NO 25

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    float shininess;
    vec3 color;
}; 

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

uniform vec3 viewPos;
uniform PointLight pointLights[MAX_LIGHT_NO];
uniform DirectionalLight directionalLights[MAX_LIGHT_NO];
uniform Material material;

out vec4 FragColor;

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
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
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
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    // Combine
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
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
        result += CalculateDirLight(directionalLights[i], norm, viewDir);

    // Point Lights
    // for(int i = 0; i < MAX_LIGHT_NO; i++)
    //     result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);

    // Spot lights
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}