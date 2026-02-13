#pragma once

#include<string>

class Shader {
	private:
		unsigned int program_id_;
		enum class CompileType {VERTEX, FRAGMENT, PROGRAM};
		
	public:
		Shader(const std::string& v_shader_path, const std::string& f_shader_path);
		unsigned int get_shader_id() const { return program_id_; }
		void use() const;
		
	private:
		void check_compile_errors(const CompileType compile_type, const unsigned int id) const;
		std::string get_compile_type_string(CompileType compile_type) const;
};