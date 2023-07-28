#version 460 core

#include "structs.glsl"
#include "functions.glsl"

layout(location = 0) out vec4 fs_out_col;

layout(std430, binding = 0) readonly buffer spheresBuffer {
    Sphere spheres[];
};

layout(std430, binding = 1) readonly buffer materialBuffer {
    Material materials[];
};

layout(location = 0) uniform vec2 window;
layout(location = 1) uniform Camera cam;
/*
layout(location = 4) uniform PointLight pointlights[2] = {
    {{-14, 12.5, 41}, 1., 0.07, .017, {0.04, 0.07, 0.01}, {0.4, 0.7f, 0.1}, {0.4, 0.7f, 0.1} },
    {{41, -10.6, 16}, 1., 0.07, .017, {0.04, 0.07, 0.01}, {0.4, 0.7f, 0.1}, {0.4, 0.7f, 0.1} }
};
*/
layout(location = 4) uniform PointLight pointlights[2] = {
{{-14, 12.5, 41}, 1.,0.0009, 0.00032, {0.04, 0.07, 0.01}, {0.4, 0.7f, 0.1}, {0.4, 0.7f, 0.1} },
{{41, -10.6, 16}, 1., 0.0009, 0.00032, {0.04, 0.07, 0.01}, {0.4, 0.7f, 0.1}, {0.4, 0.7f, 0.1} }
};

layout(location = 18) uniform float fovy;
layout(location = 19) uniform float fovx;
layout(location = 20) uniform int reflection = 1;


bool listHit(const Ray r, const float t_min, const float t_max, out HitRecord rec){
    HitRecord temp_rec;
    bool hit_anything = false;
    float closest = t_max;

    for(int i = 0; i < spheres.length(); ++i){
        if (sphereHit(spheres[i], r, t_min, closest, temp_rec)){
            hit_anything = true;
            rec = temp_rec;
            closest = temp_rec.t;
            rec.index = i;
        }
    }
    return hit_anything;
}

bool in_shadow(PointLight light, const vec3 origin){

    HitRecord ignore;
    const Ray r = {
        origin,
        normalize(light.position - origin)
    };

    return listHit(r, 0.001f, distance(light.position, origin), ignore);
}


vec3 PhongLighting(const Ray r, const PointLight light, const HitRecord rec, const bool shadow_ray){
    float dis = distance(rec.p, light.position);
    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));


    vec3 ambient = light.ambient * materials[rec.index].ambient;
//    ambient *= attenuation;

    if (shadow_ray) {
        return ambient;
    } else {
        vec3 lightDir = normalize(light.position - rec.p);
        float diff = max(dot(rec.normal, lightDir), 0.0);
        vec3 diffuse  = light.diffuse * ( diff *  materials[rec.index].diffuse);

        vec3 viewDir = -r.dir;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(rec.normal, halfwayDir), 0.0), 128 * materials[rec.index].shininess);
        vec3 specular = light.specular * (spec *  materials[rec.index].specular);

        specular *= attenuation;
        diffuse *= attenuation;
        return ambient + diffuse + specular;
    }

}
vec3 ColorRay(Ray r){
    vec3 color = vec3(0);
    vec3 sum_reflected_color = vec3(1);
    HitRecord main;
    for(int i = 0; i < reflection; ++i){
        if(listHit(r, 0.001, 1./0., main)){
            for(int j = 0; j < pointlights.length(); ++j){
                color +=  sum_reflected_color * PhongLighting(r, pointlights[j], main, in_shadow(pointlights[j], main.p));
            }

            sum_reflected_color *= materials[main.index].reflect_color;
            r.point = main.p;
            r.dir = normalize(reflect(r.dir, main.normal));
        } else {
            break;
        }
    }
    return color;
}
void main(){
    const Cameracoord camcoord = compute_cameracoord(cam);

    const float a = tan(fovx / 2) * (gl_FragCoord.x - window.x / 2)/(window.x / 2);
    const float b = tan(fovy / 2) * (window.y / 2 - gl_FragCoord.y)/(window.y / 2);

    const vec3 raypoint = cam.eye +(a * camcoord.u + b * camcoord.v - camcoord.w);
    const Ray r = {
        raypoint,
        normalize(raypoint - cam.eye)
    };

    const vec3 main_color = ColorRay(r);
    if (main_color != vec3(0)){
        fs_out_col = vec4(main_color, 1);
    } else {
        discard;
    }
}

