
#type vertex
#version 420 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_view;
uniform mat4 u_transform;

out vec3 out_normal;

void main()
{
    gl_Position = u_view * u_transform * vec4(a_position, 1.0);
    mat3 normal_mat = mat3(transpose(inverse(u_view*u_transform)));
    out_normal = normalize(normal_mat*a_normal);
}

#type geometry
#version 420 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

uniform mat4 u_proj;
in vec3 out_normal[];

void main()
{
    for(int i=0; i<3; i++)
    {
        gl_Position = u_proj*gl_in[i].gl_Position;
        EmitVertex();

        vec4 extrude = 0.1*vec4(out_normal[i], 0.0);
        gl_Position = u_proj*(gl_in[i].gl_Position + extrude);
        EmitVertex();
        EndPrimitive();
    }
}

#type fragment
#version 420 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.0, 1.0, 0.0, 1.0);
}