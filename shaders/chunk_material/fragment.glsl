#version 330 core

in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;

out vec4 frag_color;

void main() {
	const vec3 light_pos = vec3(-35, 35, -35);

	vec3 light_normal = normalize(light_pos - v_position);

	float dif = clamp(dot(v_normal, light_normal), 0., 1.);

	// vec3 diffusion_color = pow(vec3(dif), vec3(0.75)); // Gamma Correction

	frag_color = vec4(v_color * vec3(dif), 1);
}