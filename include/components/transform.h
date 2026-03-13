#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform {
	private:
		glm::vec3 position_ { 0.0f };
		glm::quat rotation_ { 1.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 scale_ { 1.0f };
		
	public:
		Transform()=default;
		
		void set_position(const glm::vec3& value) { position_ = value; }
		void set_rotation(const glm::quat& value) { rotation_ = value; }
		void set_scale(const glm::vec3& value) { scale_ = value; }
		
		const glm::vec3& get_position() const { return position_; }
		const glm::quat& get_rotation() const { return rotation_; }
		const glm::vec3& get_scale() const { return scale_; }
		
		void translate(const glm::vec3& delta);
		void rotate(const glm::quat& delta);
		void scale_by(const glm::vec3& factor);
		
		glm::mat4 matrix() const;
};