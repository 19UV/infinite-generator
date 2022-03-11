#include "graphics/renderable.hpp"

#include <iostream>
#include <cstring>

Renderable::Renderable() {
	this->VAO.attach_buffer(Vertices, 0, NULL);
	this->VAO.attach_buffer(Elements, 0, NULL);
	this->VAO.setup_vertex_attributes();
}

Renderable::~Renderable() {
	if(this->vertex_buffer != nullptr) {
		delete[] this->vertex_buffer;
	}
	if(this->indices_buffer != nullptr) {
		delete[] this->indices_buffer;
	}
}

void Renderable::fill_buffers() {
	this->VAO.bind();

	this->VAO.fill_buffer(Vertices,
		this->get_vertex_buffer_size() * sizeof(Vertex),
		this->get_vertex_buffer());
	
	this->VAO.fill_buffer(Elements,
		this->get_indices_buffer_size() * sizeof(Index),
		this->get_indices_buffer());
}

std::shared_ptr<Material>& Renderable::get_material() {
	return this->material;
}

size_t Renderable::get_vertex_buffer_size() const {
	return this->vertex_buffer_size;
}

Vertex* Renderable::get_vertex_buffer() {
	return this->vertex_buffer;
}

void Renderable::set_vertex_buffer_size(size_t num) {
	if(this->vertex_buffer != nullptr) {
		delete[] this->vertex_buffer;
	}

	this->vertex_buffer_size = num;
	this->vertex_buffer = new Vertex[num];
}

size_t Renderable::get_indices_buffer_size() const {
	return this->indices_buffer_size;
}

Index* Renderable::get_indices_buffer() {
	return this->indices_buffer;
}

void Renderable::set_indices_buffer_size(size_t num) {
	if(this->indices_buffer != nullptr) {
		delete[] this->indices_buffer;
	}

	this->indices_buffer_size = num;
	this->indices_buffer = new Index[num];
}