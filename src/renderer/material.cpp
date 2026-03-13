#include "renderer/material.h"

#include "renderer/shader.h"

void Material::bind(const Shader& shader) const {
	unsigned int slot = 0;
	
	if(albedo_) {
		albedo_->bind(slot);
		shader.set_int("material.albedo", slot);
		shader.set_int("material.has_albedo", 1);
		slot++;
	}else {
		shader.set_int("material.has_albedo", 0);
	}
	
	if(diffuse_) {
		diffuse_->bind(slot);
		shader.set_int("material.diffuse", slot);
		shader.set_int("material.has_diffuse", 1);
		slot++;
	}else {
		shader.set_int("material.has_albedo", 0);
	}
	
	if(specular_) {
		specular_->bind(slot);
		shader.set_int("material.specular", slot);
		shader.set_int("material.has_specular", 1);	
		slot++;
	}else {
		shader.set_int("material.has_specular", 0);
	}
	
	if(normal_) {
		normal_->bind(slot);
		shader.set_int("material.normal", slot);
		shader.set_int("material.has_normal", 1);
		slot++;
	}else {
		shader.set_int("material.has_normal", 0);
	}
	
	shader.set_vec4("material.base_color", base_color_);
	shader.set_float("material.shininess", shininess_);
}