#version 460 core

// pipeline-ból bejövő per-fragment attribútumok
layout(location = 0) in outVertexData{
	vec3 vs_out_pos;
	vec3 vs_out_norm;
	vec2 vs_out_tex;
};

out vec4 fs_out_col;

// irány fényforrás: fény iránya
uniform vec3 light_dir = vec3(100);

// fénytulajdonságok: ambiens, diffúz, ...
uniform vec3 La = vec3(0.4, 0.4, 0.4);
uniform vec3 Ld = vec3(0.6, 0.6, 0.6);

uniform vec3 viewPos;


uniform vec3 Ka;
uniform vec3 Ks;

uniform sampler2D map_Kd;

void main()
{

	vec3 color = texture(map_Kd, vs_out_tex).rgb;
	// ambient
	vec3 ambient = 0.2 * Ka;

	// diffuse
	vec3 lightDir = normalize(light_dir - vs_out_pos);
	vec3 normal = normalize(vs_out_norm);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	// specular
	vec3 viewDir = normalize(viewPos - vs_out_pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;

	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

	vec3 specular = Ks * spec; // assuming bright white light color
	fs_out_col = vec4(ambient + diffuse + specular, 1.0);
}