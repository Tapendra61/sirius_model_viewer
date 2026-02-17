#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer/shader.h"
#include "renderer/camera.h"

class TestCube {
	private:
			static constexpr float cube_vertices_[216] = {
		    // Positions          // Normals
		
		    // ---- Front (+Z) ----
		    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		
		     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
		
		    // ---- Back (-Z) ----
		    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		
		     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
		
		    // ---- Left (-X) ----
		    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		
		    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		
		    // ---- Right (+X) ----
		     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
		     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
		     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
		
		     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
		     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
		     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
		
		    // ---- Bottom (-Y) ----
		    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
		     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
		     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
		
		     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
		    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
		    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
		
		    // ---- Top (+Y) ----
		    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
		     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
		     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
		
		     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
		    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
		    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f
		};
		unsigned int cube_vao_ = 0, cube_vbo_ = 0;
		Shader cube_shader_;
		Camera& camera_;
		glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	
	public:
		TestCube(Camera& camera) : camera_(camera), cube_shader_("../shaders/test_cube/vertex.vert", "../shaders/test_cube/fragment.frag") {}
		
		glm::vec3 get_position() const { return position_; }
		void set_position(const glm::vec3 new_position) { position_ = new_position; }
		
		void init() {
			glGenVertexArrays(1, &cube_vao_);
			glGenBuffers(1, &cube_vbo_);
			
			glBindVertexArray(cube_vao_);
			glBindBuffer(GL_ARRAY_BUFFER, cube_vbo_);
			
			glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices_), cube_vertices_, GL_STATIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		}
		
		void draw() {
			cube_shader_.use();
			
			glm::mat4 model(1.0f);
			
			model = glm::translate(model, position_);
			glm::mat4 view = camera_.get_view_matrix();
			glm::mat4 projection = camera_.get_projection_matrix();
			
			cube_shader_.set_mat4("model", model);
			cube_shader_.set_mat4("view", view);
			cube_shader_.set_mat4("projection", projection);
			
			glBindVertexArray(cube_vao_);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
};