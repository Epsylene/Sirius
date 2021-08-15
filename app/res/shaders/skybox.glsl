
#type vertex
#version 330 core

layout (location = 0) in vec3 a_position;

out vec3 v_texCoords;

uniform mat4 u_viewProj;

void main()
{
    v_texCoords = a_position;
    vec4 pos = u_viewProj * vec4(a_position, 1.0);
    gl_Position = pos.xyww;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_texCoords;

uniform samplerCube u_skybox;

void main()
{
    color = texture(u_skybox, v_texCoords);
}
