
#type vertex
#version 420 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;

uniform mat4 u_viewProj;
uniform mat4 u_transform;
uniform mat4 u_normalMat;

out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
}


#type fragment
#version 420 core

layout(location = 0) out vec4 color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Texture
{
    vec3 texDiffuse;
    vec3 texSpecular;
};

uniform Material material;

in vec2 v_texCoord;

void main()
{
    Texture tex;

    tex.texDiffuse = texture(material.diffuse, v_texCoord).rgb;
    tex.texSpecular = texture(material.specular, v_texCoord).rgb;

    color = vec4(tex.texDiffuse + tex.texSpecular, 1.0);
}
