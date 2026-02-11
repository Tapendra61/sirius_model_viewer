#pragma once

#include "core/window.h"

class Application {
  private:
	Window window;

  public:
	Application(const unsigned int argc, char **argv, const std::string &title,
				const int width, const int height, bool vsync = false);
	void run();
	~Application();
};