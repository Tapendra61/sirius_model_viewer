#include "controllers/camera_controller.h"

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
}