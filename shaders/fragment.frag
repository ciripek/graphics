#version 460 core

#include "structs.glsl"

layout(location = 0) in vec2 test_pos;
layout(location = 0) out vec4 fs_out_col;

void main(){
    fs_out_col = vec4(test_pos, 0, 0);
}
