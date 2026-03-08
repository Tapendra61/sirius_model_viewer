#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "renderer/texture.h"
#include "renderer/shader.h"

class Material {
	private:
		std::shared_ptr<Texture> diffuse_;
		std::shared_ptr<Texture> specular_;
		std::shared_ptr<Texture> normal_;
		
		glm::vec4 base_color_ = glm::vec4(1.0f);
		float shininess_ = 32.0f;
		
	public:
		void set_diffuse(std::shared_ptr<Texture> texture) { diffuse_ = std::move(texture); }
		void set_specular(std::shared_ptr<Texture> texture) { specular_ = std::move(texture); }
		void set_normal(std::shared_ptr<Texture> texture) { normal_ = std::move(texture); }
		void set_shininess(float value) { shininess_ = value; }
		void set_base_color(const glm::vec4 value) { base_color_ = value; }
		
		void bind(const Shader& shader) const;
};