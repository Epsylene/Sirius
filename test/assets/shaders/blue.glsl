
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_viewProj;
uniform mat4 u_transform;

out vec3 v_pos;
out vec4 v_color;

void main()
{
    v_pos = a_position;
    v_color = a_color;
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_pos;

void main()
{
    color = vec4(0.11, 0.36, 1.0, 1.0);
}
