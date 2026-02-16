#include "renderer/renderer.h"

#include "sirius_logger/log.h"

void Renderer::init() {
	cube_.init();
	camera_.add_yaw(glm::radians(35.0f));
	camera_.add_pitch(glm::radians(35.0f));
}

void Renderer::render() {
	cube_.draw();
}