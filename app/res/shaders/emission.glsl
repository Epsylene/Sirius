
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_viewProj;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
