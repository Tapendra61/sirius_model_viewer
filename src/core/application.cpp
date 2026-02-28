#include "core/application.h"

#include <stdexcept>

#include "GLFW/glfw3.h"

#include "sirius_logger/log.h"
#include "core/window.h"
#include "renderer/camera.h"
#include "controllers/camera_controller.h"
#include "core/input.h"

Application::Application(const unsigned int argc, char **argv, AppConfig app_config) : app_config_(std::move(app_config)),
	camera_(app_config_.window_width, app_config_.window_height),
	camera_controller_(camera_) {
	sr::log_trace("Application Constructor body called.");
	
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
	renderer_ = std::make_unique<Renderer>(camera_);
	
	sr::log_trace("Application constructor completed.");
}

void Application::init() {
	if(initialized_) return;
	sr::log_trace("Application init called.");
	
	cube_ = std::make_unique<TestCube>(camera_);
	camera_.set_camera_target(cube_->get_position());
	Input::init(window_->get_raw_window_handle());
	renderer_->init();
	
	initialized_ = true;
}

void Application::run() {
	sr::log_trace("Application running.");
	
	init();
	
	while(!window_->should_close()) {
		compute_delta_time();
		
		window_->poll_events();
		process_input();
		camera_controller_.update(delta_time_);
		
		window_->begin_drawing();
		
		renderer_->render(cube_);
		
		window_->end_drawing();
		Input::update();
	}
}

void Application::process_input() {
	if(Input::is_key_pressed(Key::ESCAPE)) {
		window_->set_should_close(true);
	}
}

void Application::parse_arguments(const unsigned int argc, char **argv) {
	if(argc > 2) {
		sr::log_info("Too many arguments!");
		throw std::runtime_error("Too many arguments!\nUsage: sirius_model_viewer [model_path]");
	}
	
	if(argc == 2) {
		app_config_.model_path = argv[1];
	}
}

void Application::compute_delta_time() {
	float current_time = static_cast<float>(glfwGetTime());
	delta_time_ = current_time - last_time_;
	last_time_ = current_time;
}

Application::~Application() {
	window_.reset();
	glfwTerminate();
	sr::log_trace("Application terminated.");
}