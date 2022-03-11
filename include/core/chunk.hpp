#pragma once

#include <cstdint>

#include "graphics/renderable.hpp"

template<unsigned int T>
class Chunk : public Graphics::Renderable {
	public:
		Chunk(int x, int y, int z);

		void build_mesh();

		void set_block(unsigned int x, unsigned int y, unsigned int z, uint8_t value);
	
	private:
		uint16_t count_neighbors(unsigned int x, unsigned int y, unsigned int z);

		int x, y, z;
		uint8_t blocks[T][T][T];
};

// Because MSVC doesn't handle linking templates well
template class Chunk<32>;