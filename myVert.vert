#version 430

layout(location = 0) in vec3 vs_in_pos;
out vec2 test_pos;
void main()
{
	gl_Position = vec4( vs_in_pos, 1 );
	test_pos = vs_in_pos.xy;
}