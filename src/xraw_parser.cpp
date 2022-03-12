#include "xraw_parser.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

static uint8_t readUint8(std::ifstream& file) {
	uint8_t res;
	file.read((char*)&res, 1);
	return res;
}

static uint32_t readUint32(std::ifstream& file) {
	union {
		uint8_t bytes[4];
		uint32_t res;
	} res;

	file.read((char*)res.bytes, 4);

	return res.res;
}

static std::vector<uint8_t> readIndices(std::ifstream& file, uint32_t cnt) {
	std::vector<uint8_t> indices(cnt);
	for(uint32_t i = 0; i < cnt; i++) {
		indices[i] = readUint8(file);
	}
	return indices;
}

static Voxel::Material readMaterial(std::ifstream& file) {
	uint8_t red = readUint8(file),
	        green = readUint8(file),
	        blue = readUint8(file),
	        alpha = readUint8(file);
	return Voxel::Material(red, green, blue, alpha);
}

static std::array<Voxel::Material, 256> readMaterials(std::ifstream& file) {
	std::array<Voxel::Material, 256> materials;
	for(size_t i = 0; i < 256; i++) {
		materials[i] = readMaterial(file);
	}
	return materials;
}

namespace Voxel {
	Material::Material(uint8_t r, uint8_t g, uint8_t b) : Material(r, g, b, 1) { /* ... */ }

	Material::Material(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		r((float)r / 255.0f), g((float)g / 255.0f), b((float)b / 255.0f), a((float)a / 255.0f) {

		/* ... */
	}

	/* ----------------------------------------------------------------------- */

	VoxelModel::VoxelModel(uint32_t X, uint32_t Y, uint32_t Z) : X(X), Y(Y), Z(Z) { /* ... */ }

	VoxelModel VoxelModel::from_file(std::string path) {
		std::ifstream input(path, std::ios::binary);

		if (('X' != readUint8(input)) ||
		    ('R' != readUint8(input)) ||
		    ('A' != readUint8(input)) ||
		    ('W' != readUint8(input))) {
			
			throw std::runtime_error("Attempting to open non-XRAW file; Invalid File");
		}

		uint8_t color_channel_type = readUint8(input),
		        color_channel_count = readUint8(input),
		        bits_per_channel = readUint8(input),
		        bits_per_index = readUint8(input);

		if((color_channel_type != 0) ||
		   (color_channel_count != 4) ||
		   (bits_per_channel != 8) ||
		   (bits_per_index != 8)) {
		   
			throw std::runtime_error("Invalid file metadata; Read xraw_parser.cpp for more information");
		}

		uint32_t width = readUint32(input),
		         height = readUint32(input),
		         depth = readUint32(input),
		         num_colors = readUint32(input);

		if(num_colors != 256) {
			throw std::runtime_error("Non-256 Material count detected");
		}

		VoxelModel res(width, height, depth);
		res.voxels = readIndices(input, width * height * depth);
		res.materials = readMaterials(input);

		readUint8(input); // Need to set EOF flag if we reached the end of the file
		if(!input.eof()) {
			throw std::runtime_error("Parser did not reach EOF; Data Likely Corrupted; Invalid File");
		}

		return res;
	}
};