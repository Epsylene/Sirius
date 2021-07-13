
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;

uniform mat4 u_viewProj;
uniform mat4 u_transform;
uniform mat4 u_normalMat;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(u_normalMat) * a_normal;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 pos;
};

uniform Material material;
uniform Light light;

uniform vec3 u_viewDir;

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    vec3 lightDir = normalize(light.pos - v_fragPos);
    vec3 reflectDir = reflect(lightDir, v_normal);
    float diff = max(dot(v_normal, lightDir), 0.0);
    float spec = pow(max(dot(u_viewDir, reflectDir), 0), material.shininess);

    vec4 ambient = vec4(0.1 * vec3(texture(material.diffuse, v_texCoord)) * light.ambient, 1.0);
    vec4 diffuse = vec4(diff * vec3(texture(material.diffuse, v_texCoord)) * light.diffuse, 1.0);
    vec4 specular = vec4(spec * vec3(texture(material.specular, v_texCoord)) * light.specular, 1.0);

    color = ambient + diffuse + specular;
}
