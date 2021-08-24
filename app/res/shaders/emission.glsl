
#type vertex
#version 420 core

layout(location = 0) in vec3 a_position;

layout (std140, binding = 0) uniform CameraData
{
    mat4 u_viewProj;
    vec3 u_viewDir;
    vec3 u_cameraPos;
};

uniform mat4 u_transform;

void main()
{
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
}


#type fragment
#version 420 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;

void main()
{
    color = vec4(u_color, 1.0);
}
