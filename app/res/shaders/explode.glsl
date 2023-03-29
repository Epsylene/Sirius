
#type vertex
#version 420 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

layout (std140, binding = 0) uniform CameraData
{
    mat4 u_viewProj;
    vec3 u_viewDir;
    vec3 u_cameraPos;
};

uniform mat4 u_transform;

out vec3 out_normal;

void main()
{
    gl_Position = u_viewProj * vec4(a_position, 1.0);
    out_normal = a_normal;
}

// Example of a geometry shader: the geometry shader stage takes
// place between the vertex and fragment shader stages. This
// shader takes as input a set of vertices that form a primitive
// (for example a point, a line or a triangle) and allows
// transforming them as wanted before the next shader stage,
// possibly generating more vertices than were initially given.
#type geometry
#version 420 core

// We first need to declare the type of primitive input that the
// geometry shader is receiving, as well as the type of
// primitive and the number of vertices that it is outputting;
// the primitive output can only be of type "points",
// "line_strip" or "triangle_strip", however.
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;

in vec3 out_normal[];

vec4 explode(vec4 pos, vec3 normal)
{
    // Extrude the point along its normal
    vec3 dir = normal*time;
    return pos + vec4(dir, 0.0);
}

void main()
{
    // GLSL gives acces to the primitive vertices with the gl_in[]
    // array, which contains the gl_Position calculated in the
    // vertex shader stage. After updating the global gl_Position,
    // a vertex at this position is created with EmitVertex().
    gl_Position = explode(gl_in[0].gl_Position, out_normal[0]);
    EmitVertex();

    gl_Position = explode(gl_in[1].gl_Position, out_normal[0]);
    EmitVertex();

    gl_Position = explode(gl_in[2].gl_Position, out_normal[0]);
    EmitVertex();

    // After emitting the new vertices, the output primitive is
    // created with EndPrimitive(), which replaces the one
    // received as input.
    EndPrimitive();
}

#type fragment
#version 420 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.0, 1.0, 0.0, 1.0);
}