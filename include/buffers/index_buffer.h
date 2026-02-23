#pragma once

class IndexBuffer {
	private:
		unsigned int index_buffer_id_ = 0;
		unsigned int count_ = 0;
		
	public:
		IndexBuffer(unsigned int count, const unsigned int* data);
		~IndexBuffer();
		
		unsigned int get_count() const { return count_; }
		
		void bind() const;
		void unbind() const;
};