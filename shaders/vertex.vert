#version 460 core

layout(location = 0) in vec2 vs_in_pos;

void main()
{
    gl_Position = vec4(vs_in_pos, 0, 1);
}
