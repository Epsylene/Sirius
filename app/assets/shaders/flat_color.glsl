
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_viewProj;
uniform mat4 u_transform;

out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(transpose(inverse(u_transform))) * a_normal;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform vec3 u_lightPos;
uniform vec3 u_viewDir;

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    // Calculate the light direction, the "separation factor"
    // between it and the face's normal, and the reflection
    // vector of the light
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diff = max(dot(v_normal, lightDir), 0.0);
    vec3 reflectDir = reflect(lightDir, v_normal);

    // Ambient light : same everywhere in the universe
    // Diffuse light : depends on the impact of the light on the geometry
    // Specular : depends on the viewer's point of view of the geometry
    vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffuse = vec4(diff * vec3(1.0, 1.0, 1.0), 1.0);
    vec4 specular = vec4(pow(max(dot(u_viewDir, reflectDir), 0), 32) * vec3(1.0, 1.0, 1.0), 1.0);

    color = (ambient * 0.1 + diffuse + specular) * u_color;
}
