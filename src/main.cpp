#include <iostream>
#include <exception>

#include "graphics/window.hpp"

int main(int argc, char* argv[]) {
	try {
		Window window("Infinite Generator", 192*5, 108*5);
		while(!window.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(window.get_handle());

			glfwPollEvents();
		}

	} catch(std::exception& e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;

		return 1;
	}
	return 0;
}