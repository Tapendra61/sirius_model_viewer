#pragma once

#include <vector>
#include <cstdint>

#include "buffers/vertex_buffer.h"
#include "buffers/index_buffer.h"

class VertexArray {
	private:
		unsigned int vertex_array_id_ = 0;
		std::vector<const VertexBuffer*> vertex_buffers_;
		const IndexBuffer* index_buffer_ = nullptr;
		uint32_t attribute_index_counter_ = 0;
		
	public:
		VertexArray();
		VertexArray(const VertexArray&)=delete;
		VertexArray& operator=(const VertexArray&)=delete;
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;
		~VertexArray() noexcept;
		
		void bind() const;
		void unbind() const;
		
		void add_vertex_buffer(const VertexBuffer& vbo);
		void set_index_buffer(const IndexBuffer& ibo);
};