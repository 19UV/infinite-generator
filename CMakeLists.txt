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
	src/graphics/window.cpp
	
	src/main.cpp
)
add_executable(Infinite_Generator ${FILES})
set_property(TARGET Infinite_Generator PROPERTY CXX_STANDARD 11)
target_include_directories(Infinite_Generator PRIVATE include)
target_link_libraries(Infinite_Generator PRIVATE ${DEPEND})