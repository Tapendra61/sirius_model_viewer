#pragma once

#include <vector>
#include <cstdint>

#include "glm/glm.hpp"

#include "buffers/vertex_array.h"
#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};

class Mesh {
	private:
		VertexArray vao_;
		VertexBuffer vbo_;
		IndexBuffer ibo_;
		uint32_t index_count_ = 0;
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
		void draw() const;
};