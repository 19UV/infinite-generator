#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "opengl/program.hpp"

class Material {
	public:
		Material(std::string name);

		void bind();

		GLint get_attribute(std::string name);
		GLint get_uniform(std::string name);
	
	private:
		std::shared_ptr<Program> handle;

		std::unordered_map<std::string, GLint> attributes, uniforms;
};