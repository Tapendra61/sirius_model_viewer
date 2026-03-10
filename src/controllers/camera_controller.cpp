#include "controllers/camera_controller.h"

#include "glm/glm.hpp"
#include "sirius_logger/log.h"

#include "renderer/camera.h"
#include "core/input.h"

CameraController::CameraController(Camera& camera) : camera_(camera) {}

void CameraController::update(float delta_time) {
	if(Input::is_key_pressed(Key::D)) {
		camera_.add_yaw(glm::radians(move_sensitivity_ * delta_time));
	}
	if(Input::is_key_pressed(Key::A)) {
		camera_.add_yaw(glm::radians(-move_sensitivity_ * delta_time));
	}
	if(Input::is_key_pressed(Key::W)) {
		camera_.add_pitch(glm::radians(move_sensitivity_ * delta_time));
	}
	if(Input::is_key_pressed(Key::S)) {
		camera_.add_pitch(glm::radians(-move_sensitivity_ * delta_time));
	}
	if(Input::is_mouse_pressed(Mouse::LEFT_MOUSE)) {
		camera_.add_yaw(Input::get_mouse_delta().x * move_sensitivity_ * delta_time);
		camera_.add_pitch(Input::get_mouse_delta().y * move_sensitivity_ * delta_time);
	}
	else if(Input::is_mouse_pressed(Mouse::MIDDLE_MOUSE)) {
		glm::vec2 delta = Input::get_mouse_delta();
		camera_.pan(delta * pan_sensitivity_ * delta_time);
	}
	
	camera_.add_radius(-Input::get_scroll_delta() * scroll_sensitivity_);
}