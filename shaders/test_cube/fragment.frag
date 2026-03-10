#version 330 core

in vec3 normal_;
in vec3 frag_pos_;
in vec2 tex_coord_;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
};

uniform Material material;
const vec3 LIGHT_POS = vec3(1.0, 3.0, 4.0);

out vec4 frag_color_;

void main() {
	vec4 result;
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1);
	
	vec3 texture_color = texture(material.diffuse, tex_coord_).rgb;
	
	vec3 light_direction = normalize(LIGHT_POS - frag_pos_);
	vec3 normal = normalize(normal_);
	
	float diffuse_factor = max(dot(light_direction, normal), 0.0);
	
	result = diffuse_factor * vec4(texture_color, 1.0) + ambient;
	frag_color_ = result;
}