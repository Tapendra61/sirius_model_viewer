#pragma once

#include"renderer/camera.h"

class CameraController {
	private:
		Camera& camera_;
		float move_sensitivity_ = 40.0f;
		float scroll_sensitivity_ = 0.3f;
		float pan_sensitivity_ = 20.0f;
		
	public:
		CameraController(Camera& camera);
		float get_move_sensitivity() const { return move_sensitivity_; }
		float get_scroll_sensitivity() const { return scroll_sensitivity_; }
		void set_move_sensitivity(float value) { move_sensitivity_ = value; }
		void set_scroll_sensitivity(float value) { scroll_sensitivity_ = value; }
		
		void update(float delta_time);
};