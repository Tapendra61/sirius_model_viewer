#include "renderer/renderer.h"

#include <memory>

#include "sirius_logger/log.h"
#include "core/input.h"

void Renderer::init() {
	sr::log_trace("Renderer Init called.");
}

void Renderer::render(std::unique_ptr<TestCube>& cube) {
	cube->draw();
}