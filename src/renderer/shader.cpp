#include "renderer/shader.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"

#include "sirius_logger/log.h"

Shader::Shader(const std::string& v_shader_path, const std::string& f_shader_path) {
	sr::log_trace("Shader constructor: reading shader files.");
	
	std::ifstream vertex_file, fragment_file;
	std::string vertex_string, fragment_string;
	const char *vertex_src, *fragment_src;
	
	vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		std::ostringstream vertex_stream, fragment_stream;
		
		vertex_file.open(v_shader_path);
		fragment_file.open(f_shader_path);
		
		vertex_stream << vertex_file.rdbuf();
		fragment_stream << fragment_file.rdbuf();
		
		vertex_string = vertex_stream.str();
		fragment_string = fragment_stream.str();
		vertex_src = vertex_string.c_str();
		fragment_src = fragment_string.c_str();
		
		vertex_file.close();
		fragment_file.close();
	}
	catch(const std::ifstream::failure& error) {
		sr::log_error("Exception while reading/closing file. Error: {}", error.what());
	}
	
	
	unsigned int vertex_shader, fragment_shader;
	
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_src, nullptr);
	glCompileShader(vertex_shader);
	check_compile_errors(CompileType::VERTEX, vertex_shader);
	
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
	glCompileShader(fragment_shader);
	check_compile_errors(CompileType::FRAGMENT, fragment_shader);
	
	program_id_ = glCreateProgram();
	glAttachShader(program_id_, vertex_shader);
	glAttachShader(program_id_, fragment_shader);
	glLinkProgram(program_id_);
	check_compile_errors(CompileType::PROGRAM, program_id_);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::check_compile_errors(const CompileType compile_type, const unsigned int id) const {
	int success = 0;
	constexpr unsigned int log_length = 1024;
	char info_log[log_length];
	int returned_log_length = 0;
	
	if(compile_type != CompileType::PROGRAM) {		
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(id, log_length, &returned_log_length, info_log);
			sr::log_error("Failed to compile shader of type: {}! Error:\n{}", get_compile_type_string(compile_type), info_log);
			throw std::runtime_error("Shader compilation failed!");
		}
		return;
	}
	
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(id, log_length, &returned_log_length, info_log);
		sr::log_error("Failed to link program of type: {} with id {}! Error:\n{}", get_compile_type_string(compile_type), id, info_log);
		throw std::runtime_error("Program linking failed!");
	}
}

void Shader::use() const {
	glUseProgram(program_id_);
}

void Shader::set_int(const std::string& name, const int value) const {
	glUniform1i(glGetUniformLocation(program_id_, name.c_str()), value);
}

void Shader::set_float(const std::string& name, const float value) const {
	glUniform1f(glGetUniformLocation(program_id_, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
}

void Shader::set_mat3(const std::string& name, const glm::mat3& value) const {
	glUniformMatrix3fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

std::string Shader::get_compile_type_string(CompileType compile_type) const {
	switch(compile_type) {
		case CompileType::VERTEX:
			return "vertex";
		case CompileType::FRAGMENT:
			return "fragment";
		case CompileType::PROGRAM:
			return "program";
		default:
			return "unknown";
	}
}

Shader::~Shader() {
	glDeleteProgram(program_id_);
}