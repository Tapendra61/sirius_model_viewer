#include "renderer/camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(int screen_width, int screen_height, glm::vec3 camera_position, glm::vec3 camera_target, float field_of_view, float near_plane, float far_plane) :
	camera_position_(camera_position),
	camera_target_(camera_target),
	field_of_view_(field_of_view),
	near_plane_(near_plane),
	far_plane_(far_plane),
	screen_width_(screen_width),
	screen_height_(screen_height) {
	aspect_ratio_ = static_cast<float>(screen_width_) / static_cast<float>(screen_height_);
	
	update_camera_vectors();
}

void Camera::update_aspect_ratio(const int new_screen_width, const int new_screen_height) {
	aspect_ratio_ = static_cast<float>(new_screen_width) / static_cast<float>(new_screen_height);
}

glm::mat4 Camera::get_view_matrix() const {
	return glm::lookAt(camera_position_, camera_target_, world_up_);
}

glm::mat4 Camera::get_projection_matrix() const {
	if(camera_mode_ == CameraMode::ORTHOGRAPHIC) {
		return glm::ortho(0.0f, static_cast<float>(screen_width_), 0.0f, static_cast<float>(screen_height_), near_plane_, far_plane_);
	}
	
	return glm::perspective(glm::radians(field_of_view_), aspect_ratio_, near_plane_, far_plane_);
}

void Camera::add_yaw(float delta) {
	yaw_ += delta;
	update_camera_vectors();
}

void Camera::add_pitch(float delta) {
	pitch_ += delta;
	pitch_ = glm::clamp(pitch_, -89.0f, 89.0f);
	update_camera_vectors();
}

void Camera::add_radius(float delta) {
	radius_ += delta;
	radius_ = glm::max(radius_, 0.1f);
}

void Camera::update_camera_vectors() {
	glm::vec3 target(0.0f);
	target.x = radius_ * cos(yaw_) * cos(pitch_);
	target.y = radius_ * sin(pitch_);
	target.z = radius_ * sin(yaw_) * cos(pitch_);
	
	camera_position_ = target + camera_target_;
	camera_forward_ = glm::normalize(camera_target_ - camera_position_);
}