#pragma once

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"

#include "core/window.h"
#include "renderer/renderer.h"
#include "core/input.h"
#include "renderer/camera.h"
#include "controllers/camera_controller.h"
#include "model/model.h"

struct AppConfig {
	std::string model_path = "";
	std::string window_title = "";
	int window_width = 1000;
	int window_height = 1000;
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
		
		std::unique_ptr<Model> model_;
		
		bool show_file_dialog_ = false;

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
		void init_imgui() const;
		void run();
		void process_input();
		void load_new_model(const std::string& new_model_path);
		
		// UI elements
		void show_model_loader_ui();
		
		~Application();
};