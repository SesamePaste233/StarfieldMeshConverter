#pragma once
#include "Common.h"
#include "MeshIO.h"

class WavefrontWriter
{
public:
	WavefrontWriter() = default;

	~WavefrontWriter() = default;

    template <class _indices_t, class _positions_t>
    bool Write(const std::string filename, const std::string obj_name, const std::vector<_indices_t>& indices, const std::vector<_positions_t>& positions, const std::vector<std::vector<float>>& UV_list, const std::vector<std::vector<float>>& normals)
    {
        std::ofstream objFile(filename);

        if (!objFile.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return false;
        }

        objFile << "# Wavefront OBJ file" << std::endl;

        objFile << "o " << obj_name << std::endl;

        int c = 0;
        // Write vertices
        for (c = 0; c < positions.size(); c+=3) {
            objFile << "v "
                << positions[c] << " " << positions[c + 1] << " " << positions[c + 2]
                << std::endl;
        }

        // Write UVs
        for (int i = 0; i < UV_list.size(); i++) {
            objFile << "vt " << UV_list[i][0] << " " << 1.f - UV_list[i][1] << std::endl;
        }

        // Write normals
        for (int i = 0; i < normals.size(); i++) {
            objFile << "vn " << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << std::endl;
        }

        // Write faces
        for (int i = 0; i < indices.size(); i += 3) {
            objFile << "f " << indices[i] + 1 << "/" << indices[i] + 1 << "/" << indices[i] + 1 << " "
                << indices[i + 1] + 1 << "/" << indices[i + 1] + 1 << "/" << indices[i + 1] + 1 << " "
                << indices[i + 2] + 1 << "/" << indices[i + 2] + 1 << "/" << indices[i + 2] + 1
                << std::endl;
        }
        return true;
    }
};