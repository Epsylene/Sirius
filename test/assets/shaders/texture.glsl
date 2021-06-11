
#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 viewProj;
uniform mat4 transform;

out vec2 v_texCoord;

void main()
{
    v_texCoord = texCoord;
    gl_Position = viewProj * transform * vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, v_texCoord);
}
