
#type vertex
#version 420 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in vec4 a_vtxCoord;

layout (std140, binding = 0) uniform CameraData
{
    mat4 u_viewProj;
    vec3 u_viewDir;
    vec3 u_cameraPos;
};

uniform mat4 u_transform;
uniform mat4 u_normalMat;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_fragPos;
out vec3 v_viewDir;

void main()
{
    v_texCoord = a_texCoord;
    v_viewDir = u_viewDir;

    gl_Position = u_viewProj * u_transform * vec4(a_position, 1.0);
    v_fragPos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(u_normalMat) * a_normal;
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

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec4 pos;
    float attDistance;
};

struct DirectionalLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 dir;
};

struct Spotlight
{
    vec3 diffuse;
    float cosInCutoff;
    vec3 pos;
    float cosOutCutoff;
    vec3 ambient;
    float attDistance;
    vec3 dir;
};

//layout (std140, binding = 2) uniform LightData
//{
//    PointLight ptLights[10];
//    DirectionalLight dirLight;
//    Spotlight spotlight;
//} u_lightData;

layout (std140, binding = 1) uniform DirLightData
{
    DirectionalLight dirLight;
} u_dirLightData;

layout (std140, binding = 2) uniform SpotlightData
{
    Spotlight spotlight;
} u_spotlightData;

layout (std140, binding = 3) uniform PointLightsData
{
    PointLight ptLights[10];
} u_ptLightData;

uniform Material material;

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_fragPos;
in vec3 v_viewDir;

vec4 getPointLightColor(Texture tex, PointLight ptLight, vec3 viewDir, vec3 normal, vec3 fragPos);
vec4 getDirectionalLightColor(Texture tex, DirectionalLight dirLight, vec3 viewDir, vec3 normal);
vec4 getSpotlightColor(Texture tex, Spotlight spotlight, vec3 viewDir, vec3 normal, vec3 fragPos);

void main()
{
    Texture tex;

    tex.texDiffuse = texture(material.diffuse, v_texCoord).rgb;
    tex.texSpecular = texture(material.specular, v_texCoord).rgb;

    vec4 ptLightColor = vec4(0.0);

    for(int i = 0; i < 10; i++)
        ptLightColor += getPointLightColor(tex, u_ptLightData.ptLights[i], v_viewDir, v_normal, v_fragPos);

    vec4 dirLightColor = getDirectionalLightColor(tex, u_dirLightData.dirLight, v_viewDir, v_normal);
    vec4 spotlightColor = getSpotlightColor(tex, u_spotlightData.spotlight, v_viewDir, v_normal, v_fragPos);

    color = ptLightColor + dirLightColor + spotlightColor;

    //@todo: add those as options when UI and model options are done
//    color = vec4(v_normal, 1.0);
//    color = vec4(v_texCoord, 1.0, 1.0);
//    color = vec4(1.0, v_texCoord, 1.0);
//    color = vec4(vec3(gl_FragCoord.z), 1.0);
}

vec4 getPointLightColor(Texture tex, PointLight ptLight, vec3 viewDir, vec3 normal, vec3 fragPos)
{
    // Ambient component ---------------------------------------------

    // Calculate the distance between the light and the fragment, then
    // the light's attenuation factor
    float distance = length(ptLight.pos.xyz - fragPos);
    float kl = -1.0 / (ptLight.attDistance * (ptLight.attDistance - 0.001));
    float kq = 0.1 / (ptLight.attDistance * ptLight.attDistance * 0.001);
    float attenuation = 1.0 / (1.0 + distance * kl + distance * distance * kq);

    vec4 ptAmbient = vec4(attenuation * 0.1 * ptLight.ambient * tex.texDiffuse, 1.0);

    // Diffuse component ---------------------------------------------

    // Calculate the direction of the light pointing at the fragment,
    // then the scalar product between this and the surface normal
    vec3 ptLightDir = normalize(ptLight.pos.xyz - fragPos);
    float ptDiff = max(dot(normal, ptLightDir), 0.0);

    vec4 ptDiffuse = vec4(attenuation * ptDiff * ptLight.diffuse * tex.texDiffuse , 1.0);

    // Specular component ---------------------------------------------

    // Calculate the vector that is the reflection of `ptLightDir`
    // along `normal`, and then elevate the scalar product between
    // this and the camera's direction vector to `material.shininess`
    vec3 ptReflectDir = reflect(ptLightDir, normal);
    float ptSpec = pow(max(dot(viewDir, ptReflectDir), 0), material.shininess);

    vec4 ptSpecular = vec4(attenuation * ptSpec * ptLight.diffuse * tex.texSpecular, 1.0);

    return ptAmbient + ptDiffuse + ptSpecular;
}

vec4 getDirectionalLightColor(Texture tex, DirectionalLight dirLight, vec3 viewDir, vec3 normal)
{
    // Ambient component

    vec4 dirAmbient = vec4(0.1 * dirLight.ambient * tex.texDiffuse, 1.0);

    // Diffuse component

    vec3 dirLightDir = normalize(-dirLight.dir);
    float dirDiff = max(dot(normal, dirLightDir), 0.0);

    vec4 dirDiffuse = vec4(dirDiff * dirLight.diffuse * tex.texDiffuse, 1.0);

    // Specular component

    vec3 dirReflectDir = reflect(dirLightDir, normal);
    float dirSpec = pow(max(dot(viewDir, dirReflectDir), 0), material.shininess);

    vec4 dirSpecular = vec4(dirSpec * dirLight.diffuse * tex.texSpecular, 1.0);

    return dirAmbient + dirDiffuse + dirSpecular;
}

vec4 getSpotlightColor(Texture tex, Spotlight spotlight, vec3 viewDir, vec3 normal, vec3 fragPos)
{
    // Ambient component

    vec4 spotAmbient = vec4(0.1 * spotlight.ambient * tex.texDiffuse, 1.0);

    // Diffuse component

    float cosTheta = dot(normalize(spotlight.pos - v_fragPos), normalize(-spotlight.dir));
    float intensity = clamp((spotlight.cosOutCutoff - cosTheta) / (spotlight.cosOutCutoff - spotlight.cosInCutoff), 0.0, 1.0);

    float distance = length(spotlight.pos - v_fragPos);
    float kl = -1.0 / (spotlight.attDistance * (spotlight.attDistance - 0.001));
    float kq = 0.1 / (spotlight.attDistance * spotlight.attDistance * 0.001);
    float attenuation = 1.0 / (1.0 + distance * kl + distance * distance * kq);

    vec3 spotDir = normalize(spotlight.pos - v_fragPos);
    float spotDiff = max(dot(normal, spotDir), 0.0);

    vec4 spotDiffuse = vec4(attenuation * intensity * spotDiff * spotlight.diffuse * tex.texDiffuse, 1.0);

    // Specular component

    vec3 spotReflectDir = reflect(spotDir, normal);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0), material.shininess);

    vec4 spotSpecular = vec4(attenuation * intensity * spotSpec * spotlight.diffuse * tex.texSpecular, 1.0);

    return spotAmbient + spotDiffuse + spotSpecular;
}
