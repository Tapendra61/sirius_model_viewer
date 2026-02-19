#include "core/input.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


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
	mouse_delta_ = mouse_position_ - last_mouse_position_;
	last_mouse_position_ = mouse_position_;
}

glm::vec2 Input::get_mouse_delta() {
	return mouse_delta_;
}

bool Input::is_key_pressed(Key key) {
	if(!window_) return false;
	
	int glfw_key = to_glfw_key(key);
	if(glfw_key == GLFW_KEY_UNKNOWN) return false;
	
	return glfwGetKey(window_, glfw_key) == GLFW_PRESS;
}

int Input::to_glfw_key(Key key) {
	switch(key) {
		case Key::A: return GLFW_KEY_A;
		case Key::S: return GLFW_KEY_S;
		case Key::D: return GLFW_KEY_D;
		case Key::W: return GLFW_KEY_W;
		case Key::ESCAPE: return GLFW_KEY_ESCAPE;
		default: return GLFW_KEY_UNKNOWN;
	}
}

bool Input::is_mouse_pressed(Mouse mouse) {
	if(!window_) return false;
	
	int glfw_button = to_glfw_mouse(mouse);
	if(glfw_button == -1) return false;
	
	return glfwGetMouseButton(window_, glfw_button) == GLFW_PRESS;
}

int Input::to_glfw_mouse(Mouse mouse) {
	switch(mouse) {
		case Mouse::LEFT_MOUSE: return GLFW_MOUSE_BUTTON_LEFT;
		case Mouse::RIGHT_MOUSE: return GLFW_MOUSE_BUTTON_RIGHT;
		case Mouse::MIDDLE_MOUSE: return GLFW_MOUSE_BUTTON_MIDDLE;
		default: return -1;
	}
}

void Input::update() {
	mouse_delta_ = { 0.0f, 0.0f };
}