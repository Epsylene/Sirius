
#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 viewProj;
uniform mat4 transform;

out vec3 vPos;
out vec4 vColor;

void main()
{
    vPos = position;
    vColor = color;
    gl_Position = viewProj * transform * vec4(position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vPos;

void main()
{
    color = vec4(0.11, 0.36, 1.0, 1.0);
}
