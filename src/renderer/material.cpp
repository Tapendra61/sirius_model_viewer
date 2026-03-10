#include "renderer/material.h"

#include "renderer/shader.h"

void Material::bind(const Shader& shader) const {
	unsigned int slot = 0;
	
	if(albedo_) {
		albedo_->bind(slot);
		shader.set_int("material.albedo", slot);
		slot++;
	}
	
	if(diffuse_) {
		diffuse_->bind(slot);
		shader.set_int("material.diffuse", slot);
		slot++;
	}
	if(specular_) {
		specular_->bind(slot);
		shader.set_int("material.specular", slot);
		slot++;
	}
	if(normal_) {
		normal_->bind(slot);
		shader.set_int("material.normal", slot);
		slot++;
	}
	
	shader.set_vec4("material.base_color", base_color_);
	shader.set_float("material.shininess", shininess_);
}