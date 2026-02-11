#pragma once

#include <string>

struct GLFWwindow;

class Window {
  private:
	std::string title_ = "";
	int width_ = 0, height_ = 0;
	GLFWwindow *glfw_window_ = nullptr;
	bool enable_vsync_ = false;

  public:
	Window(const std::string &title, const int width, const int height,
		   bool vsync);
	GLFWwindow *get_raw_window_handle() const;
	int get_width() const { return width_; }
	int get_height() const { return height_; }

	~Window();

  private:
	static void glfw_frame_buffer_size_callback(GLFWwindow *window, int width,
												int height);
};