
#type vertex
#version 420 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_transform;

out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_transform * vec4(a_position, 0.0, 1.0);
}


#type fragment
#version 420 core

layout(location = 0) out vec4 color;

uniform sampler2D u_screenTex;

uniform int u_ppFlag;
uniform bool u_isKernel;
uniform mat3 u_kernel;
uniform float u_separator;

in vec2 v_texCoord;

void main()
{
    if(u_ppFlag == 0)
        color = vec4(texture(u_screenTex, v_texCoord).rgb, 1.0);

    if(gl_FragCoord.x > u_separator)
    {
        if(u_ppFlag == 1)
        color = vec4(1.0 - texture(u_screenTex, v_texCoord).rgb, 1.0);

        if(u_ppFlag == 2)
        {
            color = texture(u_screenTex, v_texCoord);
            float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
            color = vec4(average, average, average, 1.0);
        }

        if(u_ppFlag > 2)
        {
            const float offset = 1.0 / 500.0;
            float kernel[9];
            for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            kernel[3 * i + j] = u_kernel[i][j];

            vec2 offsets[9] = vec2[](
            vec2(-offset,  offset), // top-left
            vec2( 0.0f,    offset), // top-center
            vec2( offset,  offset), // top-right
            vec2(-offset,  0.0f),   // center-left
            vec2( 0.0f,    0.0f),   // center-center
            vec2( offset,  0.0f),   // center-right
            vec2(-offset, -offset), // bottom-left
            vec2( 0.0f,   -offset), // bottom-center
            vec2( offset, -offset)  // bottom-right
            );

            vec3 sampleTex[9];
            for(int i = 0; i < 9; i++)
            sampleTex[i] = vec3(texture(u_screenTex, v_texCoord + offsets[i]));

            vec3 col = vec3(0.0);
            for(int i = 0; i < 9; i++)
            col += sampleTex[i] * kernel[i];

            color = vec4(col, 1.0);
        }
    }
    else
    {
        color = vec4(texture(u_screenTex, v_texCoord).rgb, 1.0);
    }
}