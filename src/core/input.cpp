#include "core/input.h"

#include "GLFW/glfw3.h"

void Input::init(GLFWwindow* window) {
	window_ = window;
	glfwSetCursorPosCallback(window_, mouse_pos_callback);
}

void Input::mouse_pos_callback(GLFWwindow* window, double x_pos, double y_pos) {
	float x_position = static_cast<float>(x_pos);
	float y_position = static_cast<float>(y_pos);
	
	if(first_mouse_) {
		last_mouse_position_ = { x_position, y_position };
		mouse_position_ = { x_position, y_position };
		mouse_delta_ = {0.0f, 0.0f};
		first_mouse_ = false;
		return;
	}
	
	mouse_position_ = { x_position, y_position };
	
	mouse_delta_. = mouse_position_ - last_mouse_position_;
	last_mouse_position_ = mouse_position_;
}

glm::vec2 Input::get_mouse_delta() {
	return mouse_delta_;
}

void Input::update() {
	mouse_delta_ = { 0.0f, 0.0f };
}