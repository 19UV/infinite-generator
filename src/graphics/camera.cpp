#include "graphics/camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target, float fov) :
	position(position), target(target), fov(fov) {
	
	// Precreate View Matrix
	this->get_view_matrix();
}

void Camera::set_position(glm::vec3 position) {
	this->view_ood = true;
	this->position = position;
}

void Camera::set_target(glm::vec3 target) {
	this->view_ood = true;
	this->target = target;
}

void Camera::set_fov(float fov) {
	this->project_ood = true;
	this->fov = fov;
}

void Camera::translate(glm::vec3 delta) {
	this->set_position(this->position + delta);
	this->set_target(this->target + delta);
}

glm::mat4& Camera::get_view_matrix() {
	if(this->view_ood) {
		this->view = glm::lookAt(this->position, this->target, glm::vec3(0.0f, 1.0f, 0.0f));

		this->view_ood = false;
	}

	return this->view;
}

glm::mat4& Camera::get_projection_matrix(float width, float height) {
	const float ratio = width / height;

	if(this->project_ood || (ratio != this->projection_ratio)) {
		this->projection_ratio = ratio;

		this->projection = glm::perspective(glm::radians(this->fov), ratio, 0.1f, 1000.0f);
		this->project_ood = false;
	}
	
	return this->projection;
}