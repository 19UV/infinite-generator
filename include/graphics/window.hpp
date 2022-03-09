#pragma once

#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Window {
	public:
		Window(std::string title, unsigned int width, unsigned int height);
		Window(const Window& other) = delete;
		~Window();

		bool should_close();

		GLFWwindow* get_handle();
	
	private:
		GLFWwindow* handle = nullptr;
};