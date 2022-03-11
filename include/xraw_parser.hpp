#pragma once

#include <string>
#include <vector>
#include <array>

#include <cstdint>

namespace Voxel {
	struct Material {
		uint8_t r, g, b, a;

		Material() = default;
		Material(uint8_t r, uint8_t g, uint8_t b);
		Material(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	};

	struct VoxelModel {
		uint32_t X, Y, Z;
		std::vector<uint8_t> voxels;
		std::array<Material, 256> materials;

		VoxelModel(uint32_t X, uint32_t Y, uint32_t Z);

		static VoxelModel from_file(std::string path);
	};
};