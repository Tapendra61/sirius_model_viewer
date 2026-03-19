#version 330 core

layout (location = 0) in vec3 a_pos_;
layout (location = 1) in vec3 a_normal_;
layout (location = 2) in vec2 a_tex_coord_;
layout (location = 3) in vec3 a_tangent_;
layout (location = 4) in vec3 a_bitangent_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal_;
out vec3 frag_pos_;
out vec2 tex_coord_;
out mat3 tbn_matrix_;

void main() {
	gl_Position = projection * view * model * vec4(a_pos_, 1.0);
	mat3 normal_matrix = transpose(inverse(mat3(model)));
	normal_ = normalize(normal_matrix * a_normal_);
	frag_pos_ = vec3(model * vec4(a_pos_, 1.0));
	tex_coord_ = a_tex_coord_;
	
	vec3 tangent = normalize(normal_matrix * a_tangent_);
	vec3 normal = normalize(normal_matrix * a_normal_);
	tangent = normalize(tangent -  dot(tangent, normal) * normal);
	
	vec3 bitangent = cross(normal, tangent);
	
	tbn_matrix_ = mat3(tangent, bitangent, normal);
}