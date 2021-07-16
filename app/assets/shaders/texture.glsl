
#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;

uniform mat4 u_viewProj;
uniform mat4 u_transform;
uniform mat4 u_normalMat;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_fragPos;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(u_normalMat) * a_normal;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 pos;
    float attDistance;
};

struct DirectionalLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 dir;
};

struct Spotlight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 pos, dir;
    float cosInCutoff, cosOutCutoff, attDistance;
};

uniform Material material;
uniform PointLight ptLight;
uniform DirectionalLight dirLight;
uniform Spotlight spotlight;

uniform vec3 u_viewDir;

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_fragPos;

void main()
{
    vec3 texDiffuse = texture(material.diffuse, v_texCoord).rgb;
    vec3 texSpecular = texture(material.specular, v_texCoord).rgb;

    // ----------- POINT LIGHT

    float distance = length(ptLight.pos - v_fragPos);
    float kl = -1.0 / (ptLight.attDistance * (ptLight.attDistance - 0.001));
    float kq = 0.1 / (ptLight.attDistance * ptLight.attDistance * 0.001);
    float attenuation = 1.0 / (1.0 + distance * kl + distance * distance * kq);

    vec4 ptAmbient = vec4(attenuation * 0.1 * ptLight.ambient * texDiffuse , 1.0);

    vec3 ptLightDir = normalize(ptLight.pos - v_fragPos);
    float ptDiff = max(dot(v_normal, ptLightDir), 0.0);

    vec4 ptDiffuse = vec4(attenuation * ptDiff * ptLight.diffuse * texDiffuse , 1.0);

    vec3 ptReflectDir = reflect(ptLightDir, v_normal);
    float ptSpec = pow(max(dot(u_viewDir, ptReflectDir), 0), material.shininess);

    vec4 ptSpecular = vec4(attenuation * ptSpec * ptLight.specular * texSpecular, 1.0);

    // ----------- DIRECTIONAL LIGHT

    vec4 dirAmbient = vec4(0.1 * dirLight.ambient * texDiffuse, 1.0);

    vec3 dirLightDir = normalize(-dirLight.dir);
    float dirDiff = max(dot(v_normal, dirLightDir), 0.0);

    vec4 dirDiffuse = vec4(dirDiff * dirLight.diffuse * texDiffuse, 1.0);

    vec3 dirReflectDir = reflect(dirLightDir, v_normal);
    float dirSpec = pow(max(dot(u_viewDir, dirReflectDir), 0), material.shininess);

    vec4 dirSpecular = vec4(dirSpec * dirLight.specular * texSpecular, 1.0);

    // ----------- SPOTLIGHT

    vec4 spotAmbient = vec4(0.1 * spotlight.ambient * texDiffuse, 1.0);

    float cosTheta = dot(normalize(spotlight.pos - v_fragPos), normalize(-spotlight.dir));
    float intensity = clamp((spotlight.cosOutCutoff - cosTheta) / (spotlight.cosOutCutoff - spotlight.cosInCutoff), 0.0, 1.0);

    distance = length(spotlight.pos - v_fragPos);
    kl = -1.0 / (spotlight.attDistance * (spotlight.attDistance - 0.001));
    kq = 0.1 / (spotlight.attDistance * spotlight.attDistance * 0.001);
    attenuation = 1.0 / (1.0 + distance * kl + distance * distance * kq);

    vec3 spotDir = normalize(spotlight.pos - v_fragPos);
    float spotDiff = max(dot(v_normal, spotDir), 0.0);

    vec4 spotDiffuse = vec4(attenuation * intensity * spotDiff * spotlight.diffuse * texDiffuse, 1.0);

    vec3 spotReflectDir = reflect(spotDir, v_normal);
    float spotSpec = pow(max(dot(u_viewDir, spotReflectDir), 0), material.shininess);

    vec4 spotSpecular = vec4(attenuation * intensity * spotSpec * spotlight.specular * texSpecular, 1.0);

    // ----------- FINAL COLORS

    vec4 ambient = ptAmbient + dirAmbient + spotAmbient;
    vec4 diffuse = ptDiffuse + dirDiffuse + spotDiffuse;
    vec4 specular = ptSpecular + dirSpecular + spotSpecular;

    color = ambient + diffuse + specular;
}
