#pragma once

#include <string>
#include "glm/glm.hpp"

struct GLFWwindow;

class Window {
  private:
	std::string title_ = "";
	int width_ = 0, height_ = 0;
	GLFWwindow *glfw_window_ = nullptr;
	bool enable_vsync_ = false;
	glm::vec4 clear_color_ = glm::vec4(1.0f);

  public:
	Window(const std::string &title, const int width, const int height, bool vsync);
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	Window( Window&&) = delete;
	Window operator=(Window&&) = delete;
	
	GLFWwindow *get_raw_window_handle() const;
	int get_width() const { return width_; }
	int get_height() const { return height_; }
	
	void set_clear_color(const glm::vec4& new_color);
	void set_clear_color(const float& r, const float& g, const float& b, const float& a);
	bool should_close() const;
	void begin_drawing() const;
	void end_drawing() const;
	
	~Window();

  private:
	void poll_events() const;
	void swap_buffers() const;
	static void glfw_frame_buffer_size_callback(GLFWwindow *window, int width,
												int height);
};