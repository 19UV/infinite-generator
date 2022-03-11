#include "core/chunk.hpp"

#include <iostream>

union ChunkMaskCell {
	struct {
		uint8_t mask, count;
	} bytes;

	uint16_t res;
};

template<unsigned int T>
Chunk<T>::Chunk(int x, int y, int z) : x(x), y(y), z(z) {
	this->material = std::make_shared<Material>("chunk_material");

	for(unsigned int z = 0; z < T; z++) {
		for(unsigned int y = 0; y < T; y++) {
			for(unsigned int x = 0; x < T; x++) {
				this->blocks[z][y][x] = 0;
			}
		}
	}
}

template<unsigned int T>
void Chunk<T>::build_mesh() {
	ChunkMaskCell cell;
	uint16_t chunk_mask[T][T][T];

	size_t face_cnt = 0;
	for(unsigned int z = 0; z < T; z++) {
		for(unsigned int y = 0; y < T; y++) {
			for(unsigned int x = 0; x < T; x++) {
				if(this->blocks[z][y][x] == 0) {
					chunk_mask[z][y][x] = 0;
				} else {
					cell.res = this->count_neighbors(x, y, z);

					face_cnt += cell.bytes.count;

					chunk_mask[z][y][x] = cell.res;
				}
			}
		}
	}

	size_t vertex_count = face_cnt * 4, indices_count = face_cnt * 2;
	this->set_vertex_buffer_size(vertex_count);
	this->set_indices_buffer_size(indices_count);

	/*   4---5
	 *  /   /|
	 * 0---1 |
	 * | 6 | 7
	 * |   |/
	 * 2---3
	 *
	 * 0: (0, 1, 0), 1: (1, 1, 0), 2: (0, 0, 0), 3: (1, 0, 0)
	 * 4: (0, 1, 1), 5: (1, 1, 1), 6: (0, 0, 1), 7: (1, 0, 1)
	*/

	static unsigned int edge_indices[6][6] = {
		{ 1,3,7, 7,5,1 }, // +X
		{ 4,6,2, 2,0,4 }, // -X
		{ 4,0,1, 1,5,4 }, // +Y
		{ 2,6,7, 7,3,2 }, // -Y
		{ 5,7,6, 6,4,5 }, // +Z
		{ 0,2,3, 3,1,0 }, // -Z
	};

	static float edge_vertices[6][12] = {
		//   X        Y        Z
		{ 1,1,1,1, 1,0,1,0, 0,0,1,1 }, // +X: 1,3,5,7
		{ 0,0,0,0, 1,0,1,0, 0,0,1,1 }, // -X: 0,2,4,6
		{ 0,1,0,1, 1,1,1,1, 0,0,1,1 }, // +Y: 0,1,4,5
		{ 0,1,0,1, 0,0,0,0, 0,0,1,1 }, // -Y: 2,3,6,7
		{ 0,1,0,1, 1,1,0,0, 1,1,1,1 }, // +Z: 4,5,6,7
		{ 0,1,0,1, 1,1,0,0, 0,0,0,0 }, // -Z: 0,1,2,3
	};

	Vertex vert;
	vert.r = 1.0f;
	vert.g = 0.0f;
	vert.b = 0.0f;

	Vertex* vertex_write = this->get_vertex_buffer();
	unsigned int* indices_write = (unsigned int*)this->get_indices_buffer();
	unsigned int index_start = 0;
	for(unsigned int z = 0; z < T; z++) {
		float dz = (float)(this->z * T + z);
		for(unsigned int y = 0; y < T; y++) {
			float dy = (float)(this->y * T + y);
			for(unsigned int x = 0; x < T; x++) {
				if(chunk_mask[z][y][x] != 0) {
					float dx = (float)(this->x * T + x);

					cell.res = chunk_mask[z][y][x];

					for(unsigned int i = 0; i < 6; i++) {
						if((cell.bytes.mask >> i) & 1) {
							float* lookup = edge_vertices[i];
							for(unsigned int j = 0; j < 4; j++) {
								vert.x = dx + lookup[j];
								vert.y = dy + lookup[j + 4];
								vert.z = dz + lookup[j + 8];

								vert.r = 1.0f;
								vert.g = 0.0f;
								vert.b = 0.0f;

								*(vertex_write++) = vert;
							}

							*(indices_write++) = 0 + index_start;
							*(indices_write++) = 1 + index_start;
							*(indices_write++) = 3 + index_start;

							*(indices_write++) = 3 + index_start;
							*(indices_write++) = 2 + index_start;
							*(indices_write++) = 0 + index_start;

							index_start += 4;
						}
					}
				}
			}
		}
	}

	/*
	// Dump Vertex and Indices Buffers
	std::cout << "Vertex Count: " << this->get_vertex_buffer_size() << "\n";
	std::cout << "Triangle Count: " << this->get_indices_buffer_size() << "\n";

	std::cout << "Verticies:\n";
	for(size_t i = 0; i < this->get_vertex_buffer_size(); i++) {
		float* vert = (float*)(this->get_vertex_buffer() + i);

		std::cout << "  ";
		for(size_t j = 0; j < 9; j++) {
			std::cout << vert[j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Indicies:\n";
	for(size_t i = 0; i < this->get_indices_buffer_size(); i++) {
		unsigned int* ind = (unsigned int*)(this->get_indices_buffer() + i);

		std::cout << "  ";
		for(size_t j = 0; j < 3; j++) {
			std::cout << ind[j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	*/
}

template<unsigned int T>
void Chunk<T>::set_block(unsigned int x, unsigned int y, unsigned int z, uint8_t value) {
	if((x < T) && (y < T) && (z < T)) {
		this->blocks[z][y][x] = value;
	}
}

template<unsigned int T>
uint16_t Chunk<T>::count_neighbors(unsigned int x, unsigned int y, unsigned int z) {
	ChunkMaskCell data;
	data.res = 0;

	if((x == (T - 1)) || (this->blocks[z][y][x+1] == 0)) { // +X
		data.bytes.mask |= 1;
		data.bytes.count++;
	}

	if((x ==  0) || (this->blocks[z][y][x-1] == 0)) { // -X
		data.bytes.mask |= 2;
		data.bytes.count++;
	}

	if((y == (T - 1)) || (this->blocks[z][y+1][x] == 0)) { // +Y
		data.bytes.mask |= 4;
		data.bytes.count++;
	}

	if((y ==  0) || (this->blocks[z][y-1][x] == 0)) { // -Y
		data.bytes.mask |= 8;
		data.bytes.count++;
	}

	if((z == (T - 1)) || (this->blocks[z+1][y][x] == 0)) { // +Z
		data.bytes.mask |= 16;
		data.bytes.count++;
	}

	if((z ==  0) || (this->blocks[z-1][y][x] == 0)) { // -Z
		data.bytes.mask |= 32;
		data.bytes.count++;
	}

	return data.res;
}