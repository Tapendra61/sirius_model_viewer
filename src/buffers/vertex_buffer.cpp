#include "buffers/vertex_buffer.h"

#include "glad/glad.h"

VertexBuffer::VertexBuffer(const unsigned int size, const void* data) {
	glGenBuffers(1, &vertex_buffer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept : vertex_buffer_id_(other.vertex_buffer_id_) {
	other.vertex_buffer_id_ = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
	if(this != &other) {
		if(vertex_buffer_id_ != 0) {
			glDeleteBuffers(1, &vertex_buffer_id_);
		}
		
		vertex_buffer_id_ = other.vertex_buffer_id_;
		other.vertex_buffer_id_ = 0;
	}
	
	return *this;
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	if(vertex_buffer_id_ != 0) {
		glDeleteBuffers(1, &vertex_buffer_id_);
	}
}