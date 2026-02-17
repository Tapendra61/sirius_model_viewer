#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class Input {
	private:
		inline static GLFWwindow* window_ = nullptr;
		
		// Mouse attributes
		inline static glm::vec2 mouse_position_{0.0f};
		inline static glm::vec2 mouse_delta_{0.0f};
		inline static glm::vec2 last_mouse_position_{0.0f};
		inline static bool first_mouse_ = true;
		
	public:
		static void init(GLFWwindow* window);
		static void update();
		static glm::vec2 get_mouse_position();
		static glm::vec2 get_mouse_delta();
	private:
		static void mouse_pos_callback(GLFWwindow* window, double x_pos, double y_pos);
};