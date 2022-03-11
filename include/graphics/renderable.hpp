#pragma once

#include <memory>

#include "opengl/vertex_array.hpp"
#include "graphics/material.hpp"

namespace Graphics {
	class Renderable {
		public:
			// TODO: Add check for all OpenGL calls, to ensure that an instance of OpenGL
			// has been created. Will fix potential future segfaults.
			Renderable();
			Renderable(const Renderable& other) = delete;
			~Renderable();

			std::shared_ptr<Material>& get_material();

			void fill_buffers();

			// Used in draw call
			size_t get_indices_buffer_size() const;

		protected:
			std::shared_ptr<Material> material;

			size_t get_vertex_buffer_size() const;
			Vertex* get_vertex_buffer();
			void set_vertex_buffer_size(size_t num);

			Index* get_indices_buffer();
			void set_indices_buffer_size(size_t num);

		private:
			OpenGL::VertexArray VAO;

			Vertex* vertex_buffer = nullptr;
			size_t vertex_buffer_size = 0;
			Index* indices_buffer = nullptr;
			size_t indices_buffer_size = 0;
	};
};