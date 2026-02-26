#pragma once

class VertexBuffer{
	private:
		unsigned int vertex_buffer_id_ = 0;
	
	public:
		VertexBuffer()=default;
		VertexBuffer(const unsigned int size, const void* data);
		VertexBuffer (const VertexBuffer& )=delete;
		VertexBuffer& operator=(const VertexBuffer&)=delete;
		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;
		
		~VertexBuffer();
		
		void bind() const;
		void unbind() const;
};