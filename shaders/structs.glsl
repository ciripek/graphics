#ifndef STRUCTS_GLSL
#define STRUCTS_GLSL

#define PI 3.1415926538

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 reflect_color;
    float shininess;
};

struct Sphere {
    vec3 center;
    float radius;
};

struct Ray {
    vec3 point;
    vec3 dir;
};

struct HitRecord {
    vec3 p;
    vec3 normal;
    float t;
    int index;
};

struct Camera {
    vec3 eye, at, up;
};

struct Cameracoord{
    vec3 w, u, v;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#endif