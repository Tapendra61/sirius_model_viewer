#pragma once

#include "glm/glm.hpp"

enum class CameraMode {
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera {
	private:
		glm::vec3 camera_position_;
		glm::vec3 camera_target_;
		float radius_ = 4.0f;
		CameraMode camera_mode_ = CameraMode::PERSPECTIVE;
		float aspect_ratio_;
		float field_of_view_;
		float near_plane_;
		float far_plane_;
		int screen_width_;
		int screen_height_;
		
		const glm::vec3 world_up_ {0.0f, 1.0f, 0.0f};
		glm::vec3 camera_forward_ = glm::vec3(0.0f, 0.0f, 0.0f);
		
		float yaw_ = 0.0f;
		float pitch_ = 0.0f;
		
	public:
		Camera(int screen_width, int screen_height, glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f), float field_of_view = 45.0f, float near_plane = 0.1f, float far_plane = 100.0f);
		
		void set_camera_mode(CameraMode new_mode) { camera_mode_ = new_mode; }
		void set_camera_target(const glm::vec3& new_target) { camera_target_ = new_target; }
		void update_aspect_ratio(const int new_screen_width, const int new_screen_height);
		
		glm::mat4 get_view_matrix() const;
		glm::mat4 get_projection_matrix() const;
		
		void add_yaw(float delta);
		void add_pitch(float delta);
		void add_radius(float delta);
		
		void update_camera_vectors();
};