#pragma once

#include <memory>

#include "camera.h"
#include "test_models/test_cube.h"

class Renderer {
	private:
		
	Camera& camera_;
	
	public:
		Renderer(Camera& camera) : camera_(camera){}
		void init();
		void render(std::unique_ptr<TestCube>& cube);
};