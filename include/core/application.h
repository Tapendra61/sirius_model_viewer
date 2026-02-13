#pragma once

#include "core/window.h"
#include <memory>

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
	std::unique_ptr<Window> window;

  public:
	Application(const unsigned int argc, char **argv, AppConfig app_config = AppConfig());
	Application(const Application&)=delete;
	Application& operator=(const Application&)=delete;
	Application(Application&&)=delete;
	Application& operator=(Application&&)=delete;
	
	void run();
	~Application();
};