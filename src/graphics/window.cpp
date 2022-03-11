#include "graphics/window.hpp"

#include <iostream>

static int _window_count = 0;

// TODO: Add Mouse Controls
static void Window_cursor_position_callback(GLFWwindow* window, double x, double y) {
	Window* _this = (Window*)glfwGetWindowUserPointer(window);

	/* ... */
}

static void Window_cursor_callback(GLFWwindow* window, int button, int action, int mods) {
	if(button < 0) {
		return;
	}

	Window* _this = (Window*)glfwGetWindowUserPointer(window);

	switch(action) {
		case GLFW_PRESS:
			/* ... */
			break;
		
		case GLFW_RELEASE:
			/* ... */
			break;
		
		default:
			break;
	}
}

// TODO: Handle Resizing
static void Window_size_callback(GLFWwindow* window, int width, int height) {
	Window* _this = (Window*)glfwGetWindowUserPointer(window);

	// NOTE: Adding this feature will mean that the previous height and
	// width code will not work. Upon adding, ensure that that code is updated.

	// Also, be sure to enable window resizing in the window hints.

	/* ... */
}

// TODO: Add Correct Error Callback; Use Exception?
static void Window_error_callback(int code, const char* description) {
	/* ... */
}

Window::Window(std::string title, unsigned int width, unsigned int height) :
	width(width), height(height) {
	
	if(_window_count == 0 && !glfwInit()) {
		throw std::runtime_error("Failed to Initialize GLFW");
	}
	_window_count++;

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO: Handle Resizing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	this->handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if(!this->handle) {
		throw std::runtime_error("Failed to Create GLFW Window");
	}

	// TODO: Have it constantly ensure that its handling its own window
	// to allow for multi-window views. Although that will likely never be
	// added.
	glfwMakeContextCurrent(this->handle);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to Initialize GLAD");
	}

	if(_window_count == 1) {
		std::cout << "\n";
		std::cout << "--------------------------- OPENGL DATA ---------------------------" << "\n";
		std::cout << "OpenGL Version:       " << glGetString(GL_VERSION)                   << "\n";
		std::cout << "GLSL Version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION)  << "\n";
		std::cout << "OpenGL Driver Vendor: " << glGetString(GL_VENDOR)                    << "\n";
		std::cout << "OpenGL Renderer:      " << glGetString(GL_RENDERER)                  << "\n";
		std::cout << "-------------------------------------------------------------------" << "\n";
	}

	glfwSetWindowUserPointer(this->handle, this);
	
	/*
	glfwSetCursorPosCallback(this->handle, Window_cursor_position_callback);
	glfwSetMouseButtonCallback(this->handle, Window_cursor_callback);
	glfwSetFramebufferSizeCallback(this->handle, Window_size_callback);
	glfwSetErrorCallback(Window_error_callback);
	*/

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

Window::~Window() {
	glfwSetWindowUserPointer(this->handle, NULL);

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

void Window::bind() {
	glfwMakeContextCurrent(this->handle);
}

GLFWwindow* Window::get_handle() {
	return this->handle;
}

unsigned int Window::get_width() {
	return this->width;
}

unsigned int Window::get_height() {
	return this->height;
}