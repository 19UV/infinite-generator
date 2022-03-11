#pragma once

#include <glad/glad.h>

struct Vertex {
	float x, y, z;
	float r, g, b;
	float nx, ny, nz;
};

struct Index {
	unsigned int i[3];
};

namespace OpenGL {
	enum BufferType {
		Vertices = GL_ARRAY_BUFFER,
		Elements = GL_ELEMENT_ARRAY_BUFFER
	};

	/* I really hate this implimentation of a Vertex Array Object/Buffer abstraction,
	 * but it works, so I'm using it.
	 * I'm assuming that all Renderable objects will be using both Vertex and
	 * Element buffers.
	 *
	 * Any OpenGL Gurus, feel free to give me some pointers.
	*/
	class VertexArray {
		public:
			VertexArray();
			VertexArray(const VertexArray& other) = delete;
			~VertexArray();

			void bind();

			void attach_buffer(const BufferType type, const size_t size, const void* data);
			void fill_buffer(const BufferType type, const size_t size, const void* data);
			void setup_vertex_attributes();

			GLuint get_VAO();
			GLuint get_VBO();
			GLuint get_IBO();

		private:
			GLuint handle;

			GLuint vertex_buffer = -1, element_buffer = -1;
	};
};