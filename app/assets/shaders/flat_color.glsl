
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
    v_normal = a_normal;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform vec3 u_lightPos;

in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diff = max(dot(normalize(v_normal), lightDir), 0.0);

    vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffuse = vec4(diff * vec3(1.0, 1.0, 1.0), 1.0);
    vec4 result = (ambient * 0.1 + diffuse) * u_color;

    color = result;
}
