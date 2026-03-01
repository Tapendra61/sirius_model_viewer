#pragma once

#include <memory>

#include "camera.h"
#include "test_models/test_cube.h"
#include "model/model.h"
#include "renderer/shader.h"

class Renderer {
	private:
		
	Camera& camera_;
	Shader head_shader_;
	
	public:
		Renderer(Camera& camera) : camera_(camera), head_shader_("../shaders/test_cube/vertex.vert", "../shaders/test_cube/fragment.frag") {}
		void init();
		void render(std::unique_ptr<Model>& head_model);
};