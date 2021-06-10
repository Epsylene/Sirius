#type vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 vPos;

uniform mat4 viewProj;
uniform mat4 transform;

void main()
{
    vPos = position;
    gl_Position = viewProj * transform * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vPos;

void main()
{
    color = vec4(vPos + 0.5, 1.0);
}