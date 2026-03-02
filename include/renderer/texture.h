#pragma once

#include <string>

class Texture {
	private:
		unsigned int texture_id_ = 0;
		int width_ = 0;
		int height_ = 0;
		int channels_ = 0;
		
	public:
		Texture(const std::string& path, bool gamma_corrected = false);
		Texture(const Texture&)=delete;
		Texture& operator=(const Texture&)=delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
		
		~Texture();
		
		void bind(unsigned int slot = 0) const;
};