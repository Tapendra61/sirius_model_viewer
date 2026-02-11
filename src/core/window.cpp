#include "core/window.h"

#include <stdexcept>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "sirius_logger/log.h"

Window::Window(const std::string &title, const int width, const int height,
			   bool vsync)
	: title_(title), width_(width), height_(height), enable_vsync_(vsync) {

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfw_window_ =
		glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
	if (!glfw_window_) {
		const char *glfw_error = nullptr;
		int error_code = glfwGetError(&glfw_error);

		if (error_code != GLFW_NO_ERROR && glfw_error) {
			sr::log_error("Failed to create GLFW window! Error: {}",
						  glfw_error);
		}

		throw std::runtime_error("GLFW window creation error!");
	}

	glfwMakeContextCurrent(glfw_window_);
	if (enable_vsync_)
		glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		sr::log_error("Failed to initialize GLAD!");
		throw std::runtime_error("GLAD initialization failed!");
	}
	glfwSetWindowUserPointer(glfw_window_, this);

	glViewport(0, 0, width_, height_);
	glfwSetFramebufferSizeCallback(glfw_window_,
								   glfw_frame_buffer_size_callback);

	sr::log_info("Window constructor completed.");
}

GLFWwindow *Window::get_raw_window_handle() const { return glfw_window_; }

void Window::glfw_frame_buffer_size_callback(GLFWwindow *window, int width,
											 int height) {
	glViewport(0, 0, width, height);

	Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
	if (self) {
		self->width_ = width;
		self->height_ = height;
	}
}

Window::~Window() {
	glfwDestroyWindow(glfw_window_);
	sr::log_trace("Window destructor completed.");
}