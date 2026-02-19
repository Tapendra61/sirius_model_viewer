#include "renderer/renderer.h"

#include "sirius_logger/log.h"
#include "core/input.h"

void Renderer::init() {
	sr::log_trace("Renderer Init called.");
	
	cube_.init();
	cube_.set_position(glm::vec3(3.0f, 3.0f, 3.0f));
	camera_.add_yaw(glm::radians(30.0f));
	camera_.add_pitch(glm::radians(35.0f));
	camera_.set_camera_target(cube_.get_position());
}

void Renderer::render() {
	camera_.add_yaw(glm::radians(Input::get_mouse_delta().x));
	cube_.draw();
}