#include "core/application.h"

#include <stdexcept>

#include "GLFW/glfw3.h"

#include "core/window.h"
#include "sirius_logger/log.h"

Application::Application(const unsigned int argc, char **argv, AppConfig app_config) : app_config_(std::move(app_config)) {
	if (!glfwInit()) {
		const char *glfw_error = nullptr;
		int error_code = glfwGetError(&glfw_error);

		if (error_code != GLFW_NO_ERROR && glfw_error) {
			sr::log_error("Failed to initialize glfw! Error: {}", glfw_error);
		}

		throw std::runtime_error("GLFW initialization failed!");
	}
	parse_arguments(argc, argv);
	
	window_ = std::make_unique<Window>(app_config_.window_title, app_config_.window_width, app_config_.window_height, app_config_.enable_vsync);
	renderer_ = std::make_unique<Renderer>();
	
	sr::log_trace("Application constructor completed.");
}

void Application::run() {
	sr::log_trace("Application running.");
	
	renderer_->init();
	
	while(!window_->should_close()) {
		window_->begin_drawing();
		
		renderer_->render();
		
		window_->end_drawing();
	}
}

void Application::parse_arguments(const unsigned int argc, char **argv) {
	if(argc > 2) {
		throw std::runtime_error("Too many arguments!\nUsage: sirius_model_viewer [model_path]");
	}
	
	if(argc == 2) {
		app_config_.model_path = argv[1];
	}
}

Application::~Application() {
	window_.reset();
	glfwTerminate();
	sr::log_trace("Application terminated.");
}