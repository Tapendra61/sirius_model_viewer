#include "renderer/renderer.h"

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "sirius_logger/log.h"
#include "core/input.h"
#include "model/model.h"

void Renderer::init() {
	sr::log_trace("Renderer Init called.");
}

void Renderer::render(std::unique_ptr<Model>& model) {
	shader_.use();
	
	glm::mat4 view = camera_.get_view_matrix();
	glm::mat4 projection = camera_.get_projection_matrix();
	
	shader_.set_mat4("view", view);
	shader_.set_mat4("projection", projection);
	shader_.set_vec3("view_pos_", camera_.get_position());
		
	if(model) {
		model->draw(shader_);
	}
}