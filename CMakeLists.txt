cmake_minimum_required(VERSION 3.10)
project(Infinite_Generator)

# Dependancy Variables
set(EXTERN_GLAD  extern/glad)
set(EXTERN_GLFW  extern/glfw)
set(EXTERN_GLM   extern/glm)
set(EXTERN_IMGUI extern/imgui)

find_package(OpenGL REQUIRED)

# Build GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERN_GLFW})
set(DEPEND ${DEPEND} glfw)

# Build GLAD
add_subdirectory(${EXTERN_GLAD})
set(DEPEND ${DEPEND} glad OpenGL::GL)

# Build GLM
add_subdirectory(${EXTERN_GLM})
set(DEPEND ${DEPEND} glm)

# Build DearImgui
add_subdirectory(${EXTERN_IMGUI})
set(DEPEND ${DEPEND} imgui)

set(FILES
	# These aren't nessessary, but just incase ImGui changes its CMakeLists.txt
	${EXTERN_IMGUI}/imgui/backends/imgui_impl_opengl3.cpp
	${EXTERN_IMGUI}/imgui/backends/imgui_impl_glfw.cpp

	src/opengl/shader.cpp
	src/opengl/program.cpp
	src/opengl/vertex_array.cpp

	src/core/chunk.cpp
	
	src/graphics/window.cpp
	src/graphics/camera.cpp
	src/graphics/material.cpp
	src/graphics/renderable.cpp
	src/graphics/imgui_layer.cpp

	src/xraw_parser.cpp
	
	src/main.cpp
)
add_executable(Infinite_Generator ${FILES})
set_property(TARGET Infinite_Generator PROPERTY CXX_STANDARD 11)
target_include_directories(Infinite_Generator PRIVATE include)
target_link_libraries(Infinite_Generator PRIVATE ${DEPEND})