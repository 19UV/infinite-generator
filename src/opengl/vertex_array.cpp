#include "opengl/vertex_array.hpp"

namespace OpenGL {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &this->handle);
	}

	VertexArray::~VertexArray() {
		glBindVertexArray(this->handle);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glDeleteVertexArrays(1, &this->handle);

		if(this->vertex_buffer != -1) {
			glDeleteBuffers(1, &this->vertex_buffer);
		}
		if(this->element_buffer != -1) {
			glDeleteBuffers(1, &this->element_buffer);
		}
	}

	void VertexArray::bind() {
		glBindVertexArray(this->handle);
	}

	void VertexArray::attach_buffer(const BufferType type, const size_t size, const void* data) {
		glBindVertexArray(this->handle);

		if((type == GL_ARRAY_BUFFER) && (this->vertex_buffer != -1)) {
			glDeleteBuffers(1, &this->vertex_buffer);
		}

		if((type == GL_ELEMENT_ARRAY_BUFFER) && (this->element_buffer != -1)) {
			glDeleteBuffers(1, &this->element_buffer);
		}

		GLuint buffer;
		glGenBuffers(1, &buffer);

		glBindBuffer(type, buffer);
		glBufferData(type, size, data, GL_DYNAMIC_DRAW);

		if(type == GL_ARRAY_BUFFER) {
			this->vertex_buffer = buffer;
		} else {
			this->element_buffer = buffer;
		}
	}

	void VertexArray::fill_buffer(const BufferType type, const size_t size, const void* data) {
		glBufferData(type, size, data, GL_DYNAMIC_DRAW);
	}

	void VertexArray::setup_vertex_attributes() {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT,  GL_TRUE, sizeof(Vertex), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	GLuint VertexArray::get_VAO() {
		return this->handle;
	}

	GLuint VertexArray::get_VBO() {
		return this->vertex_buffer;
	}

	GLuint VertexArray::get_IBO() {
		return this->element_buffer;
	}
};