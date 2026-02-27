#pragma once

#include"glad/glad.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"buffers/vertex_array.h"
#include"buffers/vertex_buffer.h"
#include"buffers/buffer_layout.h"
#include"renderer/shader.h"
#include"renderer/camera.h"

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
		VertexArray cube_vao_;
		VertexBuffer cube_vbo_;
		Shader cube_shader_;
		Camera& camera_;
		glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	
	public:
		TestCube(Camera& camera) : camera_(camera), cube_shader_("../shaders/test_cube/vertex.vert", "../shaders/test_cube/fragment.frag") {}
		
		glm::vec3 get_position() const { return position_; }
		void set_position(const glm::vec3 new_position) { position_ = new_position; }
		
		void init() {
			cube_vbo_ = VertexBuffer(sizeof(cube_vertices_), cube_vertices_);
			
			BufferLayout layout;
			
			layout.push_typed<float>(0, 3);
			layout.push_typed<float>(1, 3);
			cube_vbo_.set_layout(layout);
			
			cube_vao_.add_vertex_buffer(cube_vbo_);
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
			glDrawArrays(GL_TRIANGLES, 0, 36);
			cube_vao_.unbind();
		}
};