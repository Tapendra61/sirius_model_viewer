#pragma once

#include<string>

#include "glm/glm.hpp"

class Shader {
	private:
		unsigned int program_id_;
		enum class CompileType {VERTEX, FRAGMENT, PROGRAM};
		
	public:
		Shader(const std::string& v_shader_path, const std::string& f_shader_path);
		~Shader();
		
		unsigned int get_shader_id() const { return program_id_; }
		void use() const;
		
		void set_int(const std::string& name, const int value) const;
		void set_float(const std::string& name, const float value) const;
		void set_vec2(const std::string& name, const glm::vec2& value) const;
		void set_vec3(const std::string& name, const glm::vec3& value) const;
		void set_vec4(const std::string& name, const glm::vec4& value) const;
		void set_mat3(const std::string&, const glm::mat3& value) const;
		void set_mat4(const std::string&, const glm::mat4& value) const;
		
		
	private:
		void check_compile_errors(const CompileType compile_type, const unsigned int id) const;
		std::string get_compile_type_string(CompileType compile_type) const;
};