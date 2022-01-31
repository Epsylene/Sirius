
#type vertex
#version 420 core

layout (location = 0) in vec3 a_position;

out vec3 v_texCoords;

layout (std140, binding = 0) uniform CameraData
{
    mat4 u_viewProj;
    vec3 u_viewDir;
    vec3 u_cameraPos;
};

uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_transform;

void main()
{
    v_texCoords = -a_position;
    vec4 pos = u_proj * u_view * vec4(a_position, 1.0);
    gl_Position = pos.xyww;
}

#type fragment
#version 420 core

layout(location = 0) out vec4 color;

in vec3 v_texCoords;

uniform samplerCube u_skybox;

void main()
{
    color = texture(u_skybox, v_texCoords);
}
