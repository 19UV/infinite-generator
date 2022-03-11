#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec3 a_normal;

// May want to do layout(location = n) for these
// However, that either requires
// #extension GL_ARB_explicit_uniform_location enable
// Or #version 430
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_position;
out vec3 v_color;
out vec3 v_normal;

void main() {
	v_position = a_position;
	v_color = a_color;
	v_normal = a_normal;

	gl_Position = u_projection * u_view * vec4(a_position.xyz, 1);
}