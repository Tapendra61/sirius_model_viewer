#pragma once

#include <memory>

#include "core/window.h"
#include "renderer/renderer.h"
#include "core/input.h"
#include "renderer/camera.h"
#include "controllers/camera_controller.h"
#include "model/model.h"

struct AppConfig {
	std::string model_path = "";
	std::string window_title = "";
	int window_width = 900;
	int window_height = 900;
	bool enable_vsync = false;
};

class Application {
	private:
		AppConfig app_config_;
		bool initialized_ = false;
   
		std::unique_ptr<Window> window_;
		Camera camera_;
		CameraController camera_controller_;
		std::unique_ptr<Renderer> renderer_;
		float delta_time_ = 0.0f;
		float last_time_ = 0.0f;
		
		//std::unique_ptr<TestCube> cube_; only for testing
		std::unique_ptr<Model> head_model_;

	public:
		Application(const unsigned int argc, char **argv, AppConfig app_config = AppConfig());
		Application(const Application&)=delete;
		Application& operator=(const Application&)=delete;
		Application(Application&&)=delete;
		Application& operator=(Application&&)=delete;
		
		const AppConfig& get_app_config() const { return app_config_; }
		
		void parse_arguments(const unsigned int argc, char **argv);
		
		float get_delta_time() const { return delta_time_; }
		void compute_delta_time();
		void init();
		void run();
		void process_input();
		~Application();
};