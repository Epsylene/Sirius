
#type vertex
#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = vec4(a_position, 0.0, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_screenTex;

in vec2 v_texCoord;

void main()
{
    color = vec4(texture(u_screenTex, v_texCoord).rgb, 1.0);
//    color = vec4(v_texCoord, 1.0, 1.0);
}