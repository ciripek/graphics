#ifndef FUNCTIONS_GLSL
#define FUNCTIONS_GLSL

#include "structs.glsl"

vec3 at(const Ray r, const float t){
    return r.point + t * r.dir;
}

Cameracoord compute_cameracoord(const Camera cam){
    Cameracoord coord;
    coord.w = normalize(cam.eye - cam.at);
    coord.u = normalize(cross(cam.up, coord.w));
    coord.v = cross(coord.w, coord.u);
    return coord;
}

bool sphereHit(const Sphere s, const Ray r, const float t_min, const float t_max, out HitRecord rec){
    vec3 oc = r.point - s.center;
    float a = dot(r.dir, r.dir);
    float b = dot(oc, r.dir);
    float c = dot(oc, oc) - s.radius*s.radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0){
        float temp = (-b - sqrt(b*b-a*c)) / a;

        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = at(r, rec.t);
            rec.normal = normalize(rec.p - s.center);
            return true;
        }

        temp = (-b + sqrt(b*b-a*c)) /a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = at(r, rec.t);
            rec.normal = normalize(rec.p - s.center);
            return true;
        }
    }
    return false;
}

#endif