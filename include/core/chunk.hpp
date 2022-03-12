#pragma once

#include <array>
#include <cstdint>

#include "graphics/renderable.hpp"

#include "xraw_parser.hpp"

template<unsigned int T>
class Chunk : public Graphics::Renderable {
	public:
		Chunk(int x, int y, int z);

		void build_mesh(std::array<Voxel::Material, 256>& materials);

		void set_block(unsigned int x, unsigned int y, unsigned int z, uint8_t value);
	
	private:
		uint16_t count_neighbors(unsigned int x, unsigned int y, unsigned int z);

		int x, y, z;
		uint8_t blocks[T][T][T];
};

// Because MSVC doesn't handle linking templates well
template class Chunk<32>;
template class Chunk<21>;
template class Chunk<9>;