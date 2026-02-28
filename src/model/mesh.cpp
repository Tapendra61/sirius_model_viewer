#include "model/mesh.h"

#include <vector>
#include "glad/glad.h"

#include "buffers/vertex_array.h"
#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"
#include "buffers/buffer_layout.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :
	vbo_(vertices.size() * sizeof(Vertex), vertices.data()),
	ibo_(indices.size(), indices.data()),
	index_count_(static_cast<uint32_t>(indices.size())) {
		
	BufferLayout layout;
	layout.push_typed<float>(0, 3); // position
	layout.push_typed<float>(1, 3); // normal
	layout.push_typed<float>(2, 2); // tex coord
	
	vbo_.set_layout(layout);
	
	vao_.add_vertex_buffer(vbo_);
	vao_.set_index_buffer(ibo_);
}

void Mesh::draw() const {
	vao_.bind();
	glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
	vao_.unbind();
}