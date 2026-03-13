#include "components/transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

void Transform::translate(const glm::vec3& delta) {
	position_ += delta;
}

void Transform::rotate(const glm::quat& delta) {
	rotation_ = delta * rotation_;
}

void Transform::scale_by(const glm::vec3& factor) {
	scale_ *= factor;
}

glm::mat4 Transform::matrix() const {
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position_);
	glm::mat4 rotation = glm::toMat4(rotation_);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), scale_);
	
	return translation * rotation * scale;
}