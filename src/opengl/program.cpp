#include "opengl/program.hpp"

#include <stdexcept>

namespace OpenGL {
	Program::Program(const Shader& shader0, const Shader& shader1) {
		this->handle = glCreateProgram();
		glAttachShader(this->handle, shader0.get_handle());
		glAttachShader(this->handle, shader1.get_handle());
		glLinkProgram(this->handle);
	
		int success;
		glGetProgramiv(this->handle, GL_LINK_STATUS, &success);
		if(success != GL_TRUE) {
			char info_log[512] = {0};
	
			glGetProgramInfoLog(this->handle, 512, NULL, info_log);
	
			throw std::runtime_error("Program Compilation Failed; Reason:\n  " +
				std::string(info_log));
		}
	}
	
	Program::~Program() {
		if(glIsProgram(this->handle)) {
			glDeleteProgram(this->handle);
		}
	}
	
	void Program::bind() const {
		glUseProgram(this->handle);
	}
	
	GLuint Program::get_handle() const {
		return this->handle;
	}
	
	std::shared_ptr<Program> Program::from_file(std::string name) {
		Shader vertex = Shader::from_file("./shaders/" + name + "/vertex.glsl", GL_VERTEX_SHADER);
		Shader fragment = Shader::from_file("./shaders/" + name + "/fragment.glsl", GL_FRAGMENT_SHADER);
	
		return std::make_shared<Program>(vertex, fragment);
	}
};