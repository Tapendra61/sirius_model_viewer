#pragma once

#include "camera.h"
#include "test_models/test_cube.h"

class Renderer {
	private:
		
	Camera camera_;
	TestCube cube_;
	
	public:
		Renderer() : camera_(900, 900), cube_(camera_) {}
	
		void init();
		void render();
};