
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

uniform vec3 u_matAmbient;
uniform vec3 u_matDiffuse;
uniform vec3 u_matSpecular;
uniform float u_matShininess;

uniform vec3 u_lightAmbient;
uniform vec3 u_lightDiffuse;
uniform vec3 u_lightSpecular;
uniform vec3 u_lightPos;

uniform vec3 u_viewDir;

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    // Phong reflection model

    // Calculate the light direction, the "separation factor"
    // between it and the face's normal, and the reflection
    // vector of the light
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    vec3 reflectDir = reflect(lightDir, v_normal);
    float diff = max(dot(v_normal, lightDir), 0.0);
    float spec = pow(max(dot(u_viewDir, reflectDir), 0), u_matShininess);

    // Ambient light : same everywhere in the universe
    // Diffuse light : depends on the impact of the light on the geometry
    // Specular : depends on the viewer's point of view of the geometry
    vec4 ambient = vec4(0.1 * u_matAmbient * u_lightAmbient, 1.0);
    vec4 diffuse = vec4(diff * u_matDiffuse * u_lightDiffuse, 1.0);
    vec4 specular = vec4(spec * u_matSpecular * u_lightSpecular, 1.0);

    color = ambient + diffuse + specular;
}
