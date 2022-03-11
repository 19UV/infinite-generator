#include "graphics/material.hpp"

namespace Graphics {
	Material::Material(std::string name) : handle(OpenGL::Program::from_file(name)) {}

	void Material::bind() {
		this->handle->bind();
	}

	// Ideally, I would like to just use attribute and uniform locations to
	// prevent string/map lookups EVERY FRAME. I could cache it somewhere, but
	// that may get ugly.
	// Currently not doing uniform lookups because it requires either OpenGL 4.3
	// or #extension GL_ARB_explicit_uniform_location enable, which isn't in
	// the GLAD library installed in this project.
	// TODO: Start using uniform locations.
	GLint Material::get_attribute(std::string name) {
		this->bind();
		if(this->attributes.find(name) == this->attributes.end()) {
			this->attributes[name] = glGetAttribLocation(this->handle->get_handle(), name.c_str());
		}

		return this->attributes[name];
	}

	GLint Material::get_uniform(std::string name) {
		this->bind();
		if(this->uniforms.find(name) == this->uniforms.end()) {
			this->uniforms[name] = glGetUniformLocation(this->handle->get_handle(), name.c_str());
		}

		return this->uniforms[name];
	}
};