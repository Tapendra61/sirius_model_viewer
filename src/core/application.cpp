#include "core/application.h"

#include <stdexcept>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "ImGuiFileDialog.h"


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
	
	Input::init(window_->get_raw_window_handle());
	renderer_->init();
	init_imgui();
	
	if(!app_config_.model_path.empty()) load_new_model(app_config_.model_path);
	
	initialized_ = true;
}

void Application::run() {
	sr::log_trace("Application running.");
	
	init();
	
	while(!window_->should_close()) {
		compute_delta_time();
		window_->poll_events();
		
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		process_input();
		camera_controller_.update(delta_time_);
		
		window_->begin_drawing();
		
		// render my scene
		renderer_->render(model_);
		
		show_model_loader_ui();
		
		//render imgui elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
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

void Application::init_imgui() const {
	// OpenGL Context and GLAD should be initialized before calling this function
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(window_->get_raw_window_handle(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::compute_delta_time() {
	float current_time = static_cast<float>(glfwGetTime());
	delta_time_ = current_time - last_time_;
	last_time_ = current_time;
}

void Application::show_model_loader_ui() {
	ImGui::Begin("Model Loader", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	
	ImGui::Text("Current Model: %s", app_config_.model_path.empty() ? "None" : app_config_.model_path.c_str());

	// button to load model using file explorer
	if(ImGui::Button("Open Model")) {
		IGFD::FileDialogConfig config;
		
		ImGuiFileDialog::Instance()->OpenDialog(
			"ChooseModel",
			"Choose 3D model",
			".gltf,.fbx,.obj",
			config
		);
		show_file_dialog_ = true;
	}
	
	// option to load model from explicit path
	static char new_model_path[512] = "";
	ImGui::InputText("Model Path", new_model_path, IM_ARRAYSIZE(new_model_path));
	
	if(ImGui::Button("Load From Path")) {
		if(std::string(new_model_path).length() > 0) {
			load_new_model(new_model_path);
			new_model_path[0] = '\0';
		}
	}
	
	ImGui::End();
	
	// show the file diaglo
	if(show_file_dialog_) {
		if(ImGuiFileDialog::Instance()->Display(
			"ChooseModel",
			ImGuiWindowFlags_NoCollapse,
			ImVec2(800, 600),
			ImVec2(1000, 800)
		)) {
			if(ImGuiFileDialog::Instance()->IsOk()) {
				std::string file_path = ImGuiFileDialog::Instance()->GetFilePathName();
				load_new_model(file_path);
				ImGuiFileDialog::Instance()->Close();
				show_file_dialog_ = false;
			}
			
			ImGuiFileDialog::Instance()->Close();
			show_file_dialog_ = false;
		}
	}
}

void Application::load_new_model(const std::string& new_model_path) {
	try {
		model_ = std::make_unique<Model>(new_model_path);
		model_->transform().scale_by(glm::vec3(0.8f, 0.8f, 0.8f));
		app_config_.model_path = new_model_path;
		sr::log_info("Successfully loaded new model from path: {}", new_model_path);
	}catch (const std::exception& e) {
		sr::log_error("Failed to load model from path: {}. Error: {}", new_model_path, e.what());
	}
}

Application::~Application() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	window_.reset();
	glfwTerminate();
	sr::log_trace("Application terminated.");
}