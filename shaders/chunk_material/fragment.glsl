#version 330 core

in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;

out vec4 frag_color;

void main() {
	frag_color = vec4(v_color, 1);
}