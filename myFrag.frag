#version 430

in vec2 test_pos;
out vec4 fs_out_col;

int main_index;
const float constant = 1.0, linear = 0.0009, quadratic = 0.00032;

const float PI = 3.1415926535897932384626433832795;

uniform float aspect_ratio;
uniform vec2 res;
const float fovx = 60 * PI / 180,  fovy = fovx ;
const float width = (2 * tan(fovx / 2)), height = (2 * tan(fovy / 2));

struct feny {
	vec3 pos, color;
};

struct Anyag {
	vec3 ambient, diffuse, specular;
	float shininess;
};

struct ray_t {
	vec3 p, v;
};

struct camera {
	vec3 eye, at, up;
};

struct cameracoord{
	vec3 w, u, v;
};

uniform feny fenyek[2];
uniform vec4 gombok[7];
uniform Anyag anyagok[5];
uniform camera cam;



cameracoord compute_cameracoord(camera cam){
	cameracoord ans;
	ans.w = normalize((cam.eye - cam.at));
	ans.u = normalize(cross(cam.up, ans.w));
	ans.v = cross(ans.w, ans.u);
	return ans;
}


cameracoord camcoord = compute_cameracoord(cam);

vec3 p(float i, float j){
	float a = tan(fovx / 2) * (i - width / 2)/(width/2);
	float b = tan(fovy / 2) * (height / 2 - j)/(height/2);
	return (cam.eye +(a*camcoord.u + b * camcoord.v - camcoord.w));
}

ray_t compute_ray(){
	float x = test_pos.x, y = test_pos.y;

	vec3 point = p(x,y);
	ray_t r;
	r.p = point;
	r.v = normalize(point - cam.eye);
	return r;
}

ray_t test(){
	ray_t ray;

	return ray;
}


ray_t main_ray = compute_ray(); 

vec3 point(float t, ray_t ray){
	return ray.p + t * ray.v;
}


float metszes(vec4 gomb, ray_t ray) {
	vec3 oc = ray.p - gomb.xyz;
    float a = dot(ray.v, ray.v);
    float b = 2.0 * dot(oc, ray.v);
    float c = dot(oc, oc) - gomb.w*gomb.w;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0){
	   return -1.0;
	} else if (discriminant == 0.0){
		return (-b)/(2 * a);
	} else {
		float num1 = (-b - sqrt(discriminant)) / (2.0 * a);
		float num2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (num1 > 0.0 && num2 >  0.0) {
			return min(num1, num2);
		}

		if (num1 < 0.0 && num1 < 0.0) {
			return -1.0;
		}

		return max(num1, num2);
	}
}


float metszesek(out int index, ray_t ray, int num) {
	float minimum = -1.0;
	index = -1;
	for( int i = 0; i < num ; ++i){
		float met = metszes(gombok[i], ray);
		if(!(met > 0.0)){
			continue;
		}

		if(minimum == -1.0 ||  met < minimum){
			minimum = met;
			index = i;
		}
	}

	return minimum;
}


bool is_shadow(vec3 point, vec3 light_source, vec3 normal){
	ray_t shadow_ray = {point, normalize(light_source - point)};
	int temp;
	float t = metszesek(temp, shadow_ray, 5);
	return t > 0.0;
}


vec3 Color(feny light, vec3 normal, vec3 point, bool shadow_ray){
	float dis = distance(point, light.pos);
	float attenuation = 1.0 / (constant + linear * dis + quadratic * (dis * dis));


	vec3 ambient = light.color * anyagok[main_index].ambient;
	ambient *= attenuation;
	
	if (shadow_ray) {
		return ambient;
	} else {
		vec3 lightDir = normalize(light.pos - point);
		float diff = max(dot(normal, lightDir), 0.0);
		vec3 diffuse  = light.color * ( diff *  anyagok[main_index].diffuse);

		vec3 viewDir = -main_ray.v;
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(normal, halfwayDir), 0.0), 128 * anyagok[main_index].shininess);
		vec3 specular = light.color * (spec *  anyagok[main_index].specular);

		specular *= attenuation;
		diffuse *= attenuation;
		return ambient + diffuse + specular;
	}
    
}

vec3 calculate_color(vec3 point, vec3 normal){
	vec3 color = vec3(0);

	for (int i = 0; i < 2; ++i){
		bool temp = is_shadow(point, fenyek[i].pos, normal);
		color += Color(fenyek[i], normal, point, temp);
	}
	
	return color; 
}

void main()
{
	float t = metszesek(main_index, main_ray, 7);
	if (!(t > 0.0)){
		discard;
	}

	vec3 N = normalize(point(t, main_ray) - gombok[main_index].xyz);
	if (main_index == 5 || main_index == 6){
		fs_out_col = vec4(1,1,1,1);
	} else {
		fs_out_col = vec4(calculate_color(point(t, main_ray), N), 1);
	}
	
}
