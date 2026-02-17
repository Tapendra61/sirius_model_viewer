#include "renderer/renderer.h"

#include "sirius_logger/log.h"

void Renderer::init() {
	sr::log_trace("Renderer Init called.");
	
	cube_.init();
	cube_.set_position(glm::vec3(3.0f, 3.0f, 3.0f));
	camera_.add_yaw(glm::radians(35.0f));
	camera_.add_pitch(glm::radians(35.0f));
	camera_.set_camera_target(cube_.get_position());
}

void Renderer::render() {
	camera_.add_yaw(glm::radians(0.001f));
	cube_.draw();
}