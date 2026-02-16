#version 330 core

in vec3 normal_;
in vec3 frag_pos_;

const vec3 LIGHT_POS = vec3(1.0, 3.0, 4.0);

out vec4 frag_color_;

void main() {
	vec4 result;
	vec4 ambient = vec4(0.5, 0.2, 0.6, 0.3);
	
	vec3 light_direction = normalize(LIGHT_POS - frag_pos_);
	vec3 normal = normalize(normal_);
	
	float diffuse_factor = max(dot(light_direction, normal), 0.0);
	
	result = diffuse_factor * vec4(0.5, 0.2, 0.6, 1.0) + ambient;
	frag_color_ = result;
}