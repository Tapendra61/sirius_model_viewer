#include "renderer/texture.h"

#include <cstdint>
#include <stdexcept>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "sirius_logger/log.h"

Texture::Texture(const std::string& path, bool gamma_corrected) {
	unsigned char* data = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
	if(!data) {
		sr::log_error("Failed to load texture at path: {}! Error: {}", path, stbi_failure_reason());
		throw std::runtime_error("Failed to load texture!");
	}
	
	glGenTextures(1, &texture_id_);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLenum format = 0;
	GLint internal_format = 0;
	
	if(gamma_corrected && channels_ == 1) {
		sr::log_warn("Gamma correction ignored for single channel texture.");
	}
	
	if(channels_ == 1) {
		internal_format = GL_R8;
		format = GL_RED;
	}else if(channels_ == 3) {
		internal_format = gamma_corrected ? GL_SRGB8 : GL_RGB8;
		format = GL_RGB;
	}else if(channels_ == 4) {
		internal_format = gamma_corrected ? GL_SRGB8_ALPHA8 : GL_RGBA8;
		format = GL_RGBA;
	}
	else {
		sr::log_error("Unknown image format!");
		throw std::runtime_error("Unknown image format!");
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width_, height_, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& other) noexcept :
	texture_id_(other.texture_id_),
	width_(other.width_),
	height_(other.height_),
	channels_(other.channels_) {
	other.texture_id_ = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if(this != &other) {
		if(texture_id_ != 0) glDeleteTextures(1, &texture_id_);
		texture_id_ = other.texture_id_;
		width_ = other.width_;
		height_ = other.height_;
		channels_ = other.channels_;
		other.texture_id_ = 0;
	}
	return *this;
}

void Texture::bind(unsigned int slot) const {
	GLint max_slots = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_slots);
	
	if(slot >= static_cast<unsigned int>(max_slots)) {
		sr::log_error("Specified texture slot out of maximum range! Slot range required is 0-{}.", max_slots - 1);
		throw std::runtime_error("Specified texture slot out of maximum range!");
	}

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
}

Texture::~Texture() {
	if (texture_id_ != 0) glDeleteTextures(1, &texture_id_);
}