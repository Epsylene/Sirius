
#type vertex
#version 420 core

layout (location = 0) in vec3 a_position;
layout (location = 0) in vec3 a_normal;

out vec3 v_fragPos;
out vec3 v_normal;
out vec3 v_cameraPos;

layout (std140, binding = 0) uniform CameraData
{
    mat4 viewProj;
    vec3 viewDir;
    vec3 cameraPos;
} u_cameraData;

uniform mat4 u_normalMat;
uniform mat4 u_transform;

void main()
{
    v_cameraPos = u_cameraData.cameraPos;
    v_normal = mat3(u_normalMat) * a_normal;
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    gl_Position = u_cameraData.viewProj * u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 420 core

layout(location = 0) out vec4 color;

in vec3 v_normal;
in vec3 v_fragPos;
in vec3 v_cameraPos;

uniform samplerCube u_skybox;

vec3 reflected(vec3 incident, vec3 normal)
{
    return incident - 2 * dot(incident, normal) * normal;
}

void main()
{
    // The fragment color is the sampled texture from the skybox at
    // the coordinates corresponding to the reflected vector coming
    // from the camera, along the surface normal.
    // "Realistic" :
//    vec3 I = normalize(v_fragPos - v_cameraPos);
    // Better looking :
    vec3 I = normalize(v_fragPos - v_cameraPos / 3.0);
    color = vec4(texture(u_skybox, reflected(I, normalize(v_normal))).rgb, 1.0);
}
