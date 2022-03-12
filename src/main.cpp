#include <iostream>
#include <exception>

#include "opengl/vertex_array.hpp"

#include "graphics/window.hpp"
#include "graphics/camera.hpp"
#include "graphics/material.hpp"

#include "core/chunk.hpp"

#include "xraw_parser.hpp"

int main(int argc, char* argv[]) {
	try {
		Graphics::Window window("Infinite Generator", 192*5, 108*5);
		Graphics::Camera main_camera(glm::vec3(-35.0f, 50.0f, -35.0f),
			glm::vec3(10.0f, 10.0f, 10.0f));
		
		Voxel::VoxelModel model = Voxel::VoxelModel::from_file("./examples/8_corners.xraw");
		std::cout << model.X << " " << model.Y << " " << model.Z << std::endl;

		Chunk<9> chunk(0, 0, 0);

		unsigned int i = 0;
		for(unsigned int z = 0; z < model.Z; z++) {
			for(unsigned int y = 0; y < model.Y; y++) {
				for(unsigned int x = 0; x < model.X; x++) {
					if(model.voxels[i] != 0) {
						chunk.set_block(x, y, z, model.voxels[i]);
					}
					// std::cout << ((model.voxels[i] == 0) ? '.' : 'X');

					i++;
				}
				// std::cout << "\n";
			}
			// std::cout << "\n";
		}

		/*
		Chunk<32> chunk(0, 0, 0);
		for(unsigned int i = 0; i < 32; i++) {
			chunk.set_block(i, 0, 0, 1);
			chunk.set_block(0, i, 0, 1);
			chunk.set_block(0, 0, i, 1);

			chunk.set_block(31, i, 0, 1);
			chunk.set_block(31, 0, i, 1);

			chunk.set_block(i, 31, 0, 1);
			chunk.set_block(0, 31, i, 1);

			chunk.set_block(i, 0, 31, 1);
			chunk.set_block(0, i, 31, 1);

			chunk.set_block(i, 31, 31, 1);
			chunk.set_block(31, i, 31, 1);
			chunk.set_block(31, 31, i, 1);
		}
		*/
		chunk.build_mesh(model.materials);

		glm::mat4& view_matrix = main_camera.get_view_matrix(),
			projection_matrix = main_camera.get_projection_matrix((float)window.get_width(), (float)window.get_height());

		while(!window.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			chunk.get_material()->bind();
			chunk.fill_buffers();

			glUniformMatrix4fv(chunk.get_material()->get_uniform("u_view"),
				1, GL_FALSE, (const GLfloat*)&view_matrix[0][0]);
			glUniformMatrix4fv(chunk.get_material()->get_uniform("u_projection"),
				1, GL_FALSE, (const GLfloat*)&projection_matrix[0][0]);

			glDrawElements(GL_TRIANGLES, chunk.get_indices_buffer_size() * 3, GL_UNSIGNED_INT, NULL);

			glfwSwapBuffers(window.get_handle());
			glfwPollEvents();
		}

	} catch(std::exception& e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;

		return 1;
	}
	return 0;
}