#include "core/application.h"

#include <stdexcept>

#include "GLFW/glfw3.h"

#include "core/window.h"
#include "sirius_logger/log.h"

Application::Application(const unsigned int argc, char **argv, const std::string &title, const int width, const int height, bool vsync) {
	if (!glfwInit()) {
		const char *glfw_error = nullptr;
		int error_code = glfwGetError(&glfw_error);

		if (error_code != GLFW_NO_ERROR && glfw_error) {
			sr::log_error("Failed to initialize glfw! Error: {}", glfw_error);
		}

		throw std::runtime_error("GLFW initialization failed!");
	}

	window = std::make_unique<Window>(title, width, height, vsync);
	
	sr::log_trace("Application constructor completed.");
}

void Application::run() {
	sr::log_trace("Application running.");
	
	while(!window->should_close()) {
		window->begin_drawing();
		
		window->end_drawing();
	}
}

Application::~Application() {
	window.reset();
	glfwTerminate();
	sr::log_trace("Application terminated.");
}