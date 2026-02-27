#include "buffers/index_buffer.h"

#include "glad/glad.h"

IndexBuffer::IndexBuffer(unsigned int count, const unsigned int* data) : count_(count) {
	glGenBuffers(1, &index_buffer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept : index_buffer_id_(other.index_buffer_id_), count_(other.count_) {
	other.index_buffer_id_ = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
	if(this != &other) {
		if(index_buffer_id_ != 0) {
			glDeleteBuffers(1, &index_buffer_id_);
		}
		
		index_buffer_id_ = other.index_buffer_id_;
		count_ = other.count_;
		other.index_buffer_id_ = 0;
		other.count_ = 0;
	}
	
	return *this;
}

IndexBuffer::~IndexBuffer() {
	if(index_buffer_id_ != 0) {
		glDeleteBuffers(1, &index_buffer_id_);
	}
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}