#pragma once

#include "core/window.h"
#include <memory>

class Application {
  private:
	std::unique_ptr<Window> window;

  public:
	Application(const unsigned int argc, char **argv, const std::string &title, const int width, const int height, bool vsync = false);
	Application(const Application&)=delete;
	Application& operator=(const Application&)=delete;
	Application(Application&&)=delete;
	Application& operator=(Application&&)=delete;
	
	void run();
	~Application();
};