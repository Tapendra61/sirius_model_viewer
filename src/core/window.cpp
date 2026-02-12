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
	glfwSwapInterval(enable_vsync_? 1 : 0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		sr::log_error("Failed to initialize GLAD!");
		throw std::runtime_error("GLAD initialization failed!");
	}
	glfwSetWindowUserPointer(glfw_window_, this);

	glViewport(0, 0, width_, height_);
	glfwSetFramebufferSizeCallback(glfw_window_,
								   glfw_frame_buffer_size_callback);
	
	glEnable(GL_DEPTH_TEST);
	sr::log_trace("Window constructor completed.");
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

bool Window::should_close() const {
	return glfwWindowShouldClose(glfw_window_);
}

void Window::set_clear_color(const glm::vec4& new_color) {
	clear_color_ = new_color;
}

void Window::set_clear_color(const float& r, const float& g, const float& b, const float& a) {
	clear_color_.x = r;
	clear_color_.y = g;
	clear_color_.z = b;
	clear_color_.w = a;
}

void Window::begin_drawing() const {
	glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::end_drawing() const {
	swap_buffers();
	poll_events();
}

void Window::poll_events() const {
	glfwPollEvents();
}

void Window::swap_buffers() const {
	glfwSwapBuffers(glfw_window_);
}

Window::~Window() {
	glfwDestroyWindow(glfw_window_);
	sr::log_trace("Window destructor completed.");
}