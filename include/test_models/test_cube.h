#pragma once

#include"glad/glad.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"sirius_logger/log.h"
#include"buffers/vertex_array.h"
#include"buffers/vertex_buffer.h"
#include"buffers/buffer_layout.h"
#include"renderer/shader.h"
#include"renderer/camera.h"

class TestCube {
	private:
		static constexpr float cube_vertices_[24 * 6] = {
		    // ===== Front (+Z) =====
		    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // 0
		     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // 1
		     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // 2
		    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // 3
		
		    // ===== Back (-Z) =====
		    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // 4
		     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // 5
		     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // 6
		    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // 7
		
		    // ===== Left (-X) =====
		    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  // 8
		    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  // 9
		    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  // 10
		    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  // 11
		
		    // ===== Right (+X) =====
		     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  // 12
		     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  // 13
		     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  // 14
		     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  // 15
		
		    // ===== Bottom (-Y) =====
		    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  // 16
		     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  // 17
		     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  // 18
		    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  // 19
		
		    // ===== Top (+Y) =====
		    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // 20
		     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // 21
		     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  // 22
		    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f   // 23
		};
		
		static constexpr uint32_t cube_indices_[36] = {
		    // Front
		    0, 1, 2,
		    2, 3, 0,
		
		    // Back
		    4, 6, 5,
		    6, 4, 7,
		
		    // Left
		    8, 9, 10,
		    10, 11, 8,
		
		    // Right
		    12, 14, 13,
		    14, 12, 15,
		
		    // Bottom
		    16, 18, 17,
		    18, 16, 19,
		
		    // Top
		    20, 21, 22,
		    22, 23, 20
		};
		
		VertexArray cube_vao_;
		VertexBuffer cube_vbo_;
		IndexBuffer cube_ibo_;
		Shader cube_shader_;
		Camera& camera_;
		glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	
	public:
		TestCube(Camera& camera) : camera_(camera), cube_shader_("../shaders/test_cube/vertex.vert", "../shaders/test_cube/fragment.frag") {}
		
		glm::vec3 get_position() const { return position_; }
		void set_position(const glm::vec3 new_position) { position_ = new_position; }
		
		void init() {
			cube_vbo_ = VertexBuffer(sizeof(cube_vertices_), cube_vertices_);
			cube_ibo_ = IndexBuffer(sizeof(cube_indices_)/sizeof(unsigned int), cube_indices_);
			BufferLayout layout;
			
			sr::log_info("IBO count: {}", cube_ibo_.get_count());
			
			layout.push_typed<float>(0, 3);
			layout.push_typed<float>(1, 3);
			cube_vbo_.set_layout(layout);
			
			cube_vao_.add_vertex_buffer(cube_vbo_);
			cube_vao_.set_index_buffer(cube_ibo_);
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
			
			cube_vao_.bind();
			glDrawElements(GL_TRIANGLES, cube_ibo_.get_count(), GL_UNSIGNED_INT, nullptr);
			cube_vao_.unbind();
		}
};