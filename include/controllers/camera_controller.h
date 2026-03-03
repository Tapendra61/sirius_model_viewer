#pragma once

#include"renderer/camera.h"

class CameraController {
	private:
		Camera& camera_;
		float move_sensitivity_ = 40.0f;
		float scroll_sensitivity_ = 0.3f;
		
	public:
		CameraController(Camera& camera);
		void set_sensitivity(float value) { move_sensitivity_ = value; }
		void set_scroll_sensitivity(float value) { scroll_sensitivity_ = value; }
		
		void update(float delta_time);
};