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

void Renderer::render(std::unique_ptr<Model>& head_model) {
	head_shader_.use();
	
	glm::mat4 model(1.0f);
	
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -90.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-90.0f, -0.0f, 0.0f));
	glm::mat4 view = camera_.get_view_matrix();
	glm::mat4 projection = camera_.get_projection_matrix();
	
	head_shader_.set_mat4("model", model);
	head_shader_.set_mat4("view", view);
	head_shader_.set_mat4("projection", projection);
	
	head_model->draw();
}