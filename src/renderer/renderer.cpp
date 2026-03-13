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
	
	glm::mat4 model_matrix(1.0f);
	
	model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -1.0f, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
	//model_matrix = glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(0.0f, -90.0f, 0.0f));
	//model_matrix = glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(-90.0f, -0.0f, 0.0f));
	glm::mat4 view = camera_.get_view_matrix();
	glm::mat4 projection = camera_.get_projection_matrix();
	
	shader_.set_mat4("view", view);
	shader_.set_mat4("projection", projection);
	
	model->draw(shader_, model_matrix);
}