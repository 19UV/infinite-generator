#pragma once

#include <string>
#include <memory>

#include "opengl/shader.hpp"

class Program {
	public:
		Program(const Shader& shader0, const Shader& shader1);
		Program(const Program& other) = delete;
		~Program();

		void bind() const;

		GLuint get_handle() const;

		static std::shared_ptr<Program> from_file(std::string name);

	private:
		GLuint handle = -1;
};