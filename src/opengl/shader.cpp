#include "opengl/shader.hpp"

#include <fstream>
#include <stdexcept>

Shader::Shader(const char* source, GLenum type) {
	this->handle = glCreateShader(type);
	glShaderSource(this->handle, 1, &source, NULL);
	glCompileShader(this->handle);

	int success;
	glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);
	if(success != GL_TRUE) {
		char info_log[512] = {0};

		glGetShaderInfoLog(this->handle, 512, NULL, info_log);

		throw std::runtime_error("Shader Compilation Failed; Reason:\n  " +
			std::string(info_log));
	}
}

Shader::~Shader() {
	if(glIsShader(this->handle)) {
		glDeleteShader(this->handle);
	}
}

GLuint Shader::get_handle() const {
	// Shader doesn't have protections against double frees, but it shouldn't ever be a problem
	return glIsShader(this->handle) ? this->handle : -1;
}

Shader Shader::from_file(std::string path, GLenum type) {
	std::ifstream file(path);
	std::string source_str(std::istreambuf_iterator<char>{file}, {});

	return Shader(source_str.c_str(), type);
}