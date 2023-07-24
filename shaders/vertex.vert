#version 460 core

layout(location = 0) in vec2 vs_in_pos;
layout(location = 0) out vec2 out_in_pos;

void main()
{
    gl_Position = vec4(vs_in_pos, 0, 1);
    out_in_pos = vs_in_pos.xy;
}