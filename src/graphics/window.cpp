#include "graphics/window.hpp"

#include <iostream>

static int _window_count = 0;

/*
static void Window_cursor_position_callback(GLFWwindow* window, double x, double y) {
	Window* _this = (Window*)glfwGetWindowUserPointer(window);
	
	// TODO: Have Mouse Controls
}

static void Window_cursor_callback(GLFWwindow* window, int button, int action, int mods) {
	if(button < 0) {
		return;
	}

	Window* _this = (Window*)glfwGetWindowUserPointer(window);

	// TODO: Have Mouse Controls

	switch(action) {
		case GLFW_PRESS:
			break;
		
		case GLFW_RELEASE:
			break;
		
		default:
			break;
	}
}

static void Window_size_callback(GLFWwindow* window, int width, int height) {
	Window* _this = (Window*)glfwGetWindowUserPointer(window);

	// TODO: Handle Resizing
}

static void Window_error_callback(int code, const char* description) {
	std::cerr << "[ERROR] GLFW Error " << code << ": " << description << std::endl;
}
*/

Window::Window(std::string title, unsigned int width, unsigned int height) {
	if(_window_count == 0 && !glfwInit()) {
		throw std::runtime_error("Failed to Initialize GLFW");
	}
	_window_count++;

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	// TODO: Handle Resizing
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	this->handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if(!this->handle) {
		throw std::runtime_error("Failed to Create GLFW Window");
	}

	// TODO: Have it constantly ensure that its handling its own window
	glfwMakeContextCurrent(this->handle);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to Initialize GLAD");
	}

	std::cout << "------------------------------------------------------------------" << "\n";
	std::cout << "OpenGL Version:       " << glGetString(GL_VERSION)                  << "\n";
	std::cout << "GLSL Version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	std::cout << "OpenGL Driver Vendor: " << glGetString(GL_VENDOR)                   << "\n";
	std::cout << "OpenGL Renderer:      " << glGetString(GL_RENDERER)                 << "\n";
	std::cout << "------------------------------------------------------------------" << "\n";

	glfwSetWindowUserPointer(this->handle, this);
	
	/*
	glfwSetCursorPosCallback(this->handle, Window_cursor_position_callback);
	glfwSetMouseButtonCallback(this->handle, Window_cursor_callback);
	glfwSetFramebufferSizeCallback(this->handle, Window_size_callback);
	glfwSetErrorCallback(Window_error_callback);
	*/

	glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
	if(this->handle != nullptr) {
		glfwDestroyWindow(this->handle);
	}

	// Doing --_window_count, so that it won't trigger if GLFW failed to initialize
	if((--_window_count) == 0) {
		glfwTerminate();
	}
}

bool Window::should_close() {
	return glfwWindowShouldClose(this->handle);
}

GLFWwindow* Window::get_handle() {
	return this->handle;
}