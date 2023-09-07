#version 460 core

// VBO-ból érkező változók
layout(location = 0) in vec3 vs_in_pos;
layout(location = 1) in vec3 vs_in_norm;
layout(location = 2) in vec2 vs_in_tex;
// a pipeline-ban tovább adandó értékek
layout(location = 0) out outVertexData{
    vec3 vs_out_pos;
    vec3 vs_out_norm;
    vec2 vs_out_tex;
};


out gl_PerVertex
{
    vec4 gl_Position;
};


// shader külső paraméterei
layout(location = 0) uniform mat4 MVP;
layout(location = 1) uniform mat4 world;
layout(location = 2) uniform mat4 worldIT;


void main()
{
    gl_Position = MVP * vec4(vs_in_pos, 1);

    vs_out_pos = (world * vec4(vs_in_pos, 1)).xyz;
    vs_out_norm = (worldIT * vec4(vs_in_norm, 0)).xyz;
    vs_out_tex = vs_in_tex;
}