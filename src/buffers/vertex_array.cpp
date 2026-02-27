#include"buffers/vertex_array.h"

#include"glad/glad.h"

#include<cstdint>
#include<limits>
#include<stdexcept>

#include "buffers/buffer_layout.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vertex_array_id_);
}

VertexArray::VertexArray(VertexArray&& other) noexcept :
	vertex_array_id_(other.vertex_array_id_), vertex_buffers_(std::move(other.vertex_buffers_)), index_buffer_(other.index_buffer_),
	attribute_index_counter_(other.attribute_index_counter_) {
	other.vertex_array_id_ = 0;
	other.index_buffer_ = nullptr;
	other.attribute_index_counter_ = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	if(this != &other) {
		if(vertex_array_id_ != 0) glDeleteVertexArrays(1, &vertex_array_id_);
		vertex_array_id_ = other.vertex_array_id_;
		vertex_buffers_ = std::move(other.vertex_buffers_);
		index_buffer_ = other.index_buffer_;
		attribute_index_counter_ = other.attribute_index_counter_;
		other.vertex_array_id_ = 0;
		other.index_buffer_ = nullptr;
		other.attribute_index_counter_ = 0;
	}
	
	return *this;
}

VertexArray::~VertexArray() noexcept {
	if(vertex_array_id_ != 0) glDeleteVertexArrays(1, &vertex_array_id_);
}

void VertexArray::bind() const { glBindVertexArray(vertex_array_id_); }
void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::add_vertex_buffer(const VertexBuffer& vbo) {
	bind();
	vbo.bind();
	
	const BufferLayout& layout = vbo.get_layout();
	const auto& elements = layout.get_buffer_elements();
	uint32_t stride = layout.get_stride();
	
	for(const auto& element: elements) {
		uint32_t location = (element.location == UINT32_MAX) ? attribute_index_counter_++ : element.location;
		
		glEnableVertexAttribArray(location);
		
		if(element.type == GL_FLOAT) {
			glVertexAttribPointer(location, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, stride, (const void*)(uintptr_t)element.offset);
		}
		else if(element.type == GL_UNSIGNED_INT) {
			glVertexAttribIPointer(location, element.count, element.type, stride, (const void*)(uintptr_t)element.offset);
		}
		else if(element.type == GL_UNSIGNED_BYTE) {
			glVertexAttribPointer(location, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, stride, (const void*)(uintptr_t)element.offset);
		}
		else {
			throw std::runtime_error("Unknown GL type while adding VertexBuffer in VertexArray!");
		}
	}
	
	vertex_buffers_.push_back(&vbo);
	
	unbind();
	vbo.unbind();
}

void VertexArray::set_index_buffer(const IndexBuffer& ibo) {
	bind();
	ibo.bind();
	index_buffer_ = &ibo;
	unbind();
}