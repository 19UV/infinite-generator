#pragma once

#include <string>
#include <memory>

#include <glad/glad.h>

namespace OpenGL {
	class Shader {
		public:
			Shader(const char* source, GLenum type);
			~Shader();

			GLuint get_handle() const;

			static Shader from_file(std::string path, GLenum type);

		private:
			GLuint handle = -1;
	};
};