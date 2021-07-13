
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_viewProj;
uniform mat4 u_transform;
uniform mat4 u_normalMat;

out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(u_normalMat) * a_normal;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
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

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    // Phong reflection model

    // Calculate the light direction, the "separation factor"
    // between it and the face's normal, and the reflection
    // vector of the light
    vec3 lightDir = normalize(light.pos - v_fragPos);
    vec3 reflectDir = reflect(lightDir, v_normal);
    float diff = max(dot(v_normal, lightDir), 0.0);
    float spec = pow(max(dot(u_viewDir, reflectDir), 0), material.shininess);

    // Ambient light : same everywhere in the universe
    // Diffuse light : depends on the impact of the light on the geometry
    // Specular : depends on the viewer's point of view of the geometry
    vec4 ambient = vec4(0.1 * material.ambient * light.ambient, 1.0);
    vec4 texture = vec4(diff * material.diffuse * light.diffuse, 1.0);
    vec4 specular = vec4(spec * material.specular * light.specular, 1.0);

    color = ambient + texture + specular;
}
