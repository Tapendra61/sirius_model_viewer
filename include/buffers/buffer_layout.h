#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <vector>
#include <cstdint>

struct BufferElement {
	uint32_t location;
	uint32_t count;
	GLenum type;
	bool normalized;
	uint32_t offset;
	
	BufferElement( uint32_t location = UINT32_MAX, uint32_t count = 0, GLenum type = GL_FLOAT, bool normalized = false, uint32_t offset = 0) :
	location(location), count(count), type(type), normalized(normalized), offset(offset) {}
};

class BufferLayout {
	private:
		std::vector<BufferElement> buffer_elements_;
		uint32_t stride_;
		
	public:
		BufferLayout() : stride_(0) {}
		
		// push by GL type
		void push(GLenum gl_type, unsigned int count, bool normalized = false, uint32_t location = UINT32_MAX) {
			BufferElement element(location, count, gl_type, normalized);
			buffer_elements_.push_back(element);
			recompute_offset_and_stride();
		}
		
	private:
		void recompute_offset_and_stride() {
			uint32_t offset = 0;
			for(BufferElement &element: buffer_elements_) {
				element.offset = offset;
				uint32_t size = element.count * size_of_gltype(element.type);
				offset += size;
			}
			stride_ = offset;
		}
		
		static uint32_t size_of_gltype(GLenum type) {
			switch(type) {
				case GL_FLOAT: return sizeof(float);
				case GL_UNSIGNED_INT: return sizeof(unsigned int);
				case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
				default: return 0;
			}
		}
};