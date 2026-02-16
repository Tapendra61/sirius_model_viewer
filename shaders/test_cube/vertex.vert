#version 330 core

layout (location = 0) in vec3 a_pos_;
layout (location = 1) in vec3 a_normal_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal_;
out vec3 frag_pos_;

void main() {
	gl_Position = projection * view * model * vec4(a_pos_, 1.0);
	mat3 normal_matrix = transpose(inverse(mat3(model)));
	normal_ = normalize(normal_matrix * a_normal_);
	frag_pos_ = vec3(model * vec4(a_pos_, 1.0));
}