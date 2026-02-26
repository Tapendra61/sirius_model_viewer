#pragma once

#include "buffers/buffer_layout.h"

class VertexBuffer{
	private:
		unsigned int vertex_buffer_id_ = 0;
		unsigned int size_in_bytes_ = 0;
		BufferLayout buffer_layout_;
		
	public:
		VertexBuffer()=default;
		VertexBuffer(const unsigned int size, const void* data);
		VertexBuffer (const VertexBuffer& )=delete;
		VertexBuffer& operator=(const VertexBuffer&)=delete;
		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;
		
		~VertexBuffer() noexcept;
		
		const BufferLayout& get_layout() const { return buffer_layout_; }
		void set_layout(const BufferLayout& buffer_layout) { buffer_layout_ = buffer_layout; }
		unsigned int get_size() const { return size_in_bytes_; }
		unsigned int get_id() const { return vertex_buffer_id_; }
		
		void bind() const;
		void unbind() const;
};