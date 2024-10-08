#include "MeshIO.h"
#include "Seb.h"

using namespace DirectX;
using namespace mesh;
using json = nlohmann::json;

bool MeshIO::Deserialize(const std::string filename)
{
	// Check file extension, return false if extension is not .mesh
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "mesh")
	{
		return false;
	}

	// Open the file
	std::ifstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		return false;
	}

	// Deserialize the mesh
	if (!this->Deserialize(file))
	{
		return false;
	}

	file.close();

	return true;
}

bool mesh::MeshIO::Deserialize(std::istream& file)
{
	// Load the mesh from the file
	uint32_t magic = utils::read<uint32_t>(file)[0];
	/*if (magic != 1) {
		return false;
	}*/

	std::cout << "Offset of Indices: " << std::hex << file.tellg() << std::endl;

	this->indices_size = utils::read<uint32_t>(file)[0];

	this->num_triangles = indices_size / 3;

	for (int i = 0; i < indices_size; i++) {
		auto index = utils::read<uint16_t>(file)[0];

		this->indices.emplace_back(index);
	}

	this->max_border = utils::read<float>(file)[0];

	this->num_weightsPerVertex = utils::read<uint32_t>(file)[0];

	std::cout << "Num of weights per vert: " << std::to_string(this->num_weightsPerVertex) << std::endl;

	std::cout << "Offset of Positions: " << std::hex << file.tellg() << std::endl;

	this->num_vertices = utils::read<uint32_t>(file)[0];

	this->num_positions = num_vertices * 3;

	for (int i = 0; i < num_positions; i++) {
		auto pos = utils::read<int16_t>(file)[0];
		auto d = utils::snorm_to_double(pos, max_border);

		this->positions.emplace_back(d);
	}

	std::cout << "Offset of UV1: " << std::hex << file.tellg() << std::endl;

	this->num_uv1 = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_uv1; i++) {
		auto uv1 = utils::readHalfAsFull(file, 2);
		this->UV_list1.emplace_back(uv1);
	}

	// Offset of UV2
	std::cout << "Offset of UV2: " << std::hex << file.tellg() << std::endl;

	this->num_uv2 = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_uv2; i++) {
		auto uv2 = utils::readHalfAsFull(file, 2);
		this->UV_list2.emplace_back(uv2);
	}

	std::cout << "Offset of Vertex Colors: " << std::hex << file.tellg() << std::endl;

	this->num_vert_colors = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_vert_colors; i++) {
		auto color = utils::read<uint8_t>(file, 4);
		this->vert_colors.push_back({ color[0],color[1],color[2],color[3] });
	}

	std::cout << "Offset of Normals: " << std::hex << file.tellg() << std::endl;

	this->num_normals = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_normals; i++) {
		auto n = utils::read<uint32_t>(file)[0];
		auto normal = utils::decodeDEC3N(n);
		this->normals.emplace_back(normal);
	}

	std::cout << "Offset of Tangents: " << std::hex << file.tellg() << std::endl;

	this->num_tangents = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_tangents; i++) {
		auto t = utils::read<uint32_t>(file)[0];
		float w = 0;
		auto tangent = utils::decodeDEC3N_w(t, w);
		this->tangents.emplace_back(tangent);
		this->tangent_signs.emplace_back(w);
	}

	std::cout << "Offset of Weights: " << std::hex << file.tellg() << std::endl;

	this->num_weights = utils::read<uint32_t>(file)[0];
	auto num_entires = 0;
	if (this->num_weights != 0) {
		num_entires = this->num_vertices;
	}

	for (int i = 0; i < num_entires; i++) {
		vertex_weight vw = new bone_binding[num_weightsPerVertex];

		for (int j = 0; j < num_weightsPerVertex; j++) {
			auto pair = utils::read<uint16_t>(file, 2);
			vw[j].bone = pair[0];
			vw[j].weight = pair[1];
			if (pair[1] > 0) {
				if (pair[0] >= this->weight_indices.size())
				{
					this->weight_indices.resize(pair[0] + 1);
				}
				this->weight_indices[pair[0]].emplace_back(i);
			}
		}

		this->weights.emplace_back(vw);
	}

	std::cout << "Offset of LoDs: " << std::hex << file.tellg() << std::endl;

	this->num_lods = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_lods; i++) {
		auto num_lod = utils::read<uint32_t>(file)[0];
		std::vector<uint16_t> lod;
		for (int j = 0; j < num_lod; j++) {
			auto index = utils::read<uint16_t>(file)[0];
			lod.emplace_back(index);
		}
		this->lods.emplace_back(lod);
	}

	std::cout << "Offset of Meshlets: " << std::hex << file.tellg() << std::endl;

	this->num_meshlets = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < num_meshlets; i++) {
		Meshlet ml;
		auto data = utils::read<uint32_t>(file, 4);

		ml.VertCount = data[0];
		ml.VertOffset = data[1];
		ml.PrimCount = data[2];
		ml.PrimOffset = data[3];

		this->meshlets.emplace_back(ml);
	}

	std::cout << "Offset of Culldata: " << std::hex << file.tellg() << std::endl;

	this->num_culldata = utils::read<uint32_t>(file)[0];
	for (int i = 0; i < num_meshlets; i++) {
		auto buffer = utils::readBytes(file, sizeof(BSCullData));
		BSCullData cd;
		memcpy(&cd, buffer, sizeof(BSCullData));

		this->culldata.emplace_back(cd);

		// Release buffer
		delete[] buffer;
	}
	// Print max border
	std::cout << "Border: " << std::to_string(this->max_border) << std::endl;

	// Print vertex number
	std::cout << "Vertex count: " << std::to_string(this->num_vertices) << std::endl;

	// Print triangle number
	std::cout << "Face count: " << std::to_string(this->num_triangles) << std::endl;

	// Print vertex color number
	std::cout << "Vertex color count: " << std::to_string(this->num_vert_colors) << std::endl;

	// Print vertex weight number
	std::cout << "Vertex weight count: " << std::to_string(this->num_weightsPerVertex == 0 ? 0 : this->num_weights / this->num_weightsPerVertex) << std::endl;

	// Print LoD number
	std::cout << "LoD count: " << std::to_string(this->num_lods) << std::endl;

	// Print meshlet number
	std::cout << "Meshlet count: " << std::to_string(this->num_meshlets) << std::endl;

	// Print culldata number
	std::cout << "Culldata count: " << std::to_string(this->num_culldata) << std::endl;

	return true;
}

bool MeshIO::Serialize(const std::string filename)
{
	std::ofstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error: Failed to open file." << std::endl;
		return false;
	}

	if (!this->Serialize(file))
	{
		std::cout << "Error: Failed to serialize mesh." << std::endl;
		return false;
	}

	file.close();

	return true;
}

bool mesh::MeshIO::Serialize(std::ostream& file)
{
	uint32_t magic = 2;
	utils::writeAsHex(file, magic);

	uint32_t dummy = 0;

	// Print vertex number
	std::cout << "Vertex count: " << std::to_string(this->num_vertices) << std::endl;

	// Print triangle number
	std::cout << "Face count: " << std::to_string(this->num_triangles) << std::endl;

	// Print vertex color number
	std::cout << "Vertex color count: " << std::to_string(this->num_vert_colors) << std::endl;

	// Print number of weights per vertex
	std::cout << "Number of weights per vertex: " << std::to_string(this->num_weightsPerVertex) << std::endl;

	// Print vertex weight number
	std::cout << "Vertex weight count: " << std::to_string(this->num_weightsPerVertex == 0 ? 0 : this->num_weights / this->num_weightsPerVertex) << std::endl;

	// Print meshlet number
	std::cout << "Meshlet count: " << std::to_string(this->num_meshlets) << std::endl;

	// Print culldata number
	std::cout << "Culldata count: " << std::to_string(this->num_culldata) << std::endl;

	if (export_geometry) {
		this->indices_size = this->indices.size();
		utils::writeAsHex(file, this->indices_size);
		for (auto index : this->indices) {
			utils::writeAsHex(file, index);
		}

		utils::writeAsHex(file, this->max_border);

		if (export_weights) {
			utils::writeAsHex(file, this->num_weightsPerVertex);
		}
		else {
			utils::writeAsHex(file, dummy);
		}

		this->num_vertices = this->positions.size() / 3;
		utils::writeAsHex(file, this->num_vertices);

		for (auto pos : this->positions) {
			auto p = utils::double_to_snorm(pos, this->max_border);
			utils::writeAsHex(file, p);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
		utils::writeAsHex(file, this->max_border);
		if (export_weights) {
			utils::writeAsHex(file, this->num_weightsPerVertex);
		}
		else {
			utils::writeAsHex(file, dummy);
		}
		utils::writeAsHex(file, dummy);
	}

	if (export_uvs) {
		this->num_uv1 = this->UV_list1.size();
		utils::writeAsHex(file, this->num_uv1);

		for (auto uv1 : this->UV_list1) {
			auto u = utils::floatToHalf(uv1[0]);
			auto v = utils::floatToHalf(uv1[1]);
			utils::writeAsHex(file, u);
			utils::writeAsHex(file, v);
		}

		this->num_uv2 = this->UV_list2.size();
		utils::writeAsHex(file, this->num_uv2);

		for (auto uv2 : this->UV_list2) {
			auto u = utils::floatToHalf(uv2[0]);
			auto v = utils::floatToHalf(uv2[1]);
			utils::writeAsHex(file, u);
			utils::writeAsHex(file, v);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
		utils::writeAsHex(file, dummy);
	}

	if (export_vert_colors) {
		this->num_vert_colors = this->vert_colors.size();
		utils::writeAsHex(file, this->num_vert_colors);

		for (auto color : this->vert_colors) {
			utils::writeAsHex(file, color.b);
			utils::writeAsHex(file, color.g);
			utils::writeAsHex(file, color.r);
			utils::writeAsHex(file, color.a);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	if (export_normals) {
		this->num_normals = this->normals.size();
		utils::writeAsHex(file, this->num_normals);

		for (auto normal : this->normals) {
			auto n = utils::encodeDEC3N(normal, 1);
			utils::writeAsHex(file, n);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	if (export_tangents) {
		this->num_tangents = this->tangents.size();
		utils::writeAsHex(file, this->num_tangents);

		for (int i = 0; i < this->num_vertices; ++i) {
			auto t = utils::encodeDEC3N(this->tangents[i], this->tangent_signs[i]);
			utils::writeAsHex(file, t);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	if (export_weights) {
		this->num_weights = this->weights.size() * this->num_weightsPerVertex;
		utils::writeAsHex(file, this->num_weights);

		for (auto vw : this->weights) {
			for (int j = 0; j < this->num_weightsPerVertex; j++) {
				utils::writeAsHex(file, vw[j].bone);
				utils::writeAsHex(file, vw[j].weight);
			}
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	utils::writeAsHex(file, this->num_lods);

	if (export_meshlets) {
		this->num_meshlets = this->meshlets.size();
		utils::writeAsHex(file, this->num_meshlets);

		for (auto meshlet : this->meshlets) {
			utils::writeAsHex(file, meshlet.VertCount);
			utils::writeAsHex(file, meshlet.VertOffset);
			utils::writeAsHex(file, meshlet.PrimCount);
			utils::writeAsHex(file, meshlet.PrimOffset);
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	if (export_culldata) {
		this->num_culldata = this->culldata.size();
		utils::writeAsHex(file, this->num_culldata);

		for (auto& culldata : this->culldata) {
			utils::writeStream(file, &culldata, sizeof(BSCullData));
		}
	}
	else {
		utils::writeAsHex(file, dummy);
	}

	return true;
}

template<typename T>
inline bool _larger_then_replace(T& target, const T& value) {
	if (value > target) {
		target = value;
		return true;
	}
	return false;
}

bool MeshIO::GeometryFromJson(const json& jsonData, float scale_factor) {
	const json& positionsRaw = jsonData["positions_raw"];

	float pos_max = 0;

	if (positionsRaw.is_array()) {
		this->num_positions = positionsRaw.size();
		this->num_vertices = this->num_positions / 3;
		for (const auto& element : positionsRaw) {
			if (element.is_number()) {
				float _pos = float(element) * scale_factor;
				if (abs(_pos) > pos_max) {
					pos_max = abs(_pos);
				}
				this->positions.emplace_back(_pos);
			}
		}
	}
	else {
		std::cout << "Error: 'positions_raw' is not an array." << std::endl;
		return false;
	}
	// To prevent overflow
	this->max_border = pos_max + 0.2;

	if (this->max_border < 1) {
		this->max_border = 1;
	}

	if (this->num_vertices > uint16_t(-1)) {
		std::cout << "Error: Number of vertices has exceeded the maximum amount of 65535. Please split the mesh into smaller pieces before encoding." << std::endl;
		return false;
	}

	float settings_max_border = jsonData["max_border"];
	if (settings_max_border > pos_max) {
		this->max_border = settings_max_border;
	}
	else {
		if (settings_max_border != 0)
			std::cout << "Warning: Max border too low." << std::endl;
	}

	const json& indicesRaw = jsonData["vertex_indices_raw"];

	if (indicesRaw.is_array()) {
		this->indices_size = indicesRaw.size();
		this->num_triangles = this->indices_size / 3;
		for (const auto& element : indicesRaw) {
			if (element.is_number()) {
				uint16_t _index = element;
				this->indices.emplace_back(_index);
			}
		}
	}
	else {
		std::cout << "Error: 'vertex_indices_raw' is not an array." << std::endl;
		return false;
	}

	
	const json& UVData = jsonData["uv_coords"];

	if (UVData.is_array()) {
		// Check if length of UVData is equal to the number of vertices
		if (UVData.size() > 0 && UVData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'uv_coords' is not equal to the number of vertices." << std::endl;
			return false;
		}

		this->num_uv1 = UVData.size();
		for (const auto& uv : UVData) {
			if (uv.is_array()) {
				if (uv.size() != 2) {
					std::cout << "Error: Length of 'uv_coords' is not equal to 2." << std::endl;
					return false;
				}

				std::vector<float> uv_l;
				for (const auto& element : uv) {
					if (element.is_number()) {
						float _uv = element;
						uv_l.push_back(_uv);
					}
				}
				this->UV_list1.push_back(uv_l);
			}
		}
	}
	else {
		std::cout << "Error: 'uv_coords' is not an array." << std::endl;
		return false;
	}

	if (jsonData.contains("uv_coords2")) {
		const json& UVData2 = jsonData["uv_coords2"];

		if (UVData2.is_array()) {
			// Check if length of UVData is equal to the number of vertices
			if (UVData2.size() > 0 && UVData2.size() != this->num_vertices) {
				std::cout << "Error: Length of 'uv_coords2' is not equal to the number of vertices." << std::endl;
				return false;
			}

			this->num_uv2 = UVData2.size();
			for (const auto& uv : UVData2) {
				if (uv.is_array()) {
					if (uv.size() != 2) {
						std::cout << "Error: Length of 'uv_coords2' is not equal to 2." << std::endl;
						return false;
					}

					std::vector<float> uv_l;
					for (const auto& element : uv) {
						if (element.is_number()) {
							float _uv = element;
							uv_l.push_back(_uv);
						}
					}
					this->UV_list2.push_back(uv_l);
				}
			}
		}
		else {
			std::cout << "Error: 'uv_coords2' is not an array." << std::endl;
			return false;
		}
	}

	return true;
}

bool mesh::MeshIO::GeometryFromOBJ(const std::string filename, float scale_factor)
{
	WaveFrontReader<uint16_t> wfr;

	if (wfr.Load(utils::charToWchar(filename.c_str())) != S_OK) {
		return false;
	}

	std::swap(this->indices, wfr.indices);
	
	for (auto& v : wfr.vertices) {
		this->positions.emplace_back(v.position.x * scale_factor);
		_larger_then_replace(this->max_border, abs(v.position.x * scale_factor));

		this->positions.emplace_back(v.position.y * scale_factor);
		_larger_then_replace(this->max_border, abs(v.position.y * scale_factor));

		this->positions.emplace_back(v.position.z * scale_factor);
		_larger_then_replace(this->max_border, abs(v.position.z * scale_factor));

		std::vector<float> uv = { v.textureCoordinate.x, v.textureCoordinate.y };
		this->UV_list1.emplace_back(uv);
	}

	this->indices_size = this->indices.size();
	this->num_triangles = this->indices.size() / 3;

	this->num_positions = this->positions.size();
	this->num_vertices = this->positions.size() / 3;

	this->num_uv1 = this->UV_list1.size();

	if (this->max_border < 1) {
		this->max_border = 1;
	}

	return true;
}

bool MeshIO::LoadFromString(const std::string json_data, const float scale_factor, const uint32_t options) {
	this->Clear();

	json jsonData = json::parse(json_data);

	std::cout << "Loading mesh from string..." << std::endl;

	return this->LoadFromJson(jsonData, scale_factor, options);
}

bool MeshIO::LoadFromNumpy(
	const std::string json_header,
	const float* ptr_positions,
	const int64_t* ptr_indices,
	const float* ptr_normals,
	const float* ptr_uv1,
	const float* ptr_uv2,
	const float* ptr_color,
	const float* ptr_tangents,
	const int32_t* ptr_bitangent_signs,
	const uint32_t options
) {
	this->Clear();

	json jsonData = json::parse(json_header);

	return this->LoadFromNumpyJson(jsonData, ptr_positions, ptr_indices, ptr_normals, ptr_uv1, ptr_uv2, ptr_color, ptr_tangents, ptr_bitangent_signs, options);
}

bool MeshIO::LoadFromNumpyJson(const nlohmann::json& jsonData,
	const float* ptr_positions,
	const int64_t* ptr_indices,
	const float* ptr_normals,
	const float* ptr_uv1,
	const float* ptr_uv2,
	const float* ptr_color,
	const float* ptr_tangents,
	const int32_t* ptr_bitangent_signs,
	const uint32_t options
) {
	this->Clear();

	std::cout << "Loading mesh from numpy..." << std::endl;

	this->num_positions = jsonData["num_verts"] * 3;
	this->num_vertices = jsonData["num_verts"];

	if (this->num_vertices > uint16_t(-1)) {
		std::cout << "Error: Number of vertices has exceeded the maximum amount of 65535. Please split the mesh into smaller pieces before encoding." << std::endl;
		return false;
	}

	float pos_max = 0;

	if (ptr_positions == nullptr) {
		if (jsonData.contains("ptr_positions")) {
			ptr_positions = (float*)static_cast<uintptr_t>(jsonData["ptr_positions"]);
			std::cout << "ptr_positions: " << (uintptr_t)ptr_positions << std::endl;
		}
		else {
			std::cout << "Error: 'positions' is null." << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < this->num_vertices; ++i) {
		this->positions.emplace_back(ptr_positions[i * 3 + 0]);
		if (abs(ptr_positions[i * 3 + 0]) > pos_max) pos_max = abs(ptr_positions[i * 3 + 0]);
		this->positions.emplace_back(ptr_positions[i * 3 + 1]);
		if (abs(ptr_positions[i * 3 + 1]) > pos_max) pos_max = abs(ptr_positions[i * 3 + 1]);
		this->positions.emplace_back(ptr_positions[i * 3 + 2]);
		if (abs(ptr_positions[i * 3 + 2]) > pos_max) pos_max = abs(ptr_positions[i * 3 + 2]);
	}

	// To prevent overflow
	this->max_border = pos_max + 0.1;

	float settings_max_border = jsonData["max_border"];
	if (settings_max_border > pos_max) {
		this->max_border = settings_max_border;
	}
	else {
		if (settings_max_border != 0)
			std::cout << "Warning: Max border too low." << std::endl;
	}

	this->indices_size = jsonData["num_indices"];
	this->num_triangles = this->indices_size / 3;

	if (ptr_indices == nullptr) {
		if (jsonData.contains("ptr_indices")) {
			ptr_indices = (int64_t*)static_cast<uintptr_t>(jsonData["ptr_indices"]);
			std::cout << "ptr_indices: " << (uintptr_t)ptr_indices << std::endl;
		}
		else {
			std::cout << "Error: 'indices' is null." << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < this->indices_size; ++i) {
		this->indices.emplace_back(ptr_indices[i]);
	}

	if (ptr_uv1 == nullptr) {
		if (jsonData.contains("ptr_uv1")) {
			ptr_uv1 = (float*)static_cast<uintptr_t>(jsonData["ptr_uv1"]);
			std::cout << "ptr_uv1: " << (uintptr_t)ptr_uv1 << std::endl;
		}
		else {
			std::cout << "Error: 'uv1' is null." << std::endl;
			return false;
		}
	}

	this->num_uv1 = this->num_vertices;
	for (size_t i = 0; i < this->num_uv1; ++i) {
		std::vector<float> uv = { ptr_uv1[i * 2 + 0], ptr_uv1[i * 2 + 1] };
		this->UV_list1.emplace_back(uv);
	}

	if (ptr_uv2 == nullptr) {
		if (jsonData.contains("ptr_uv2")) {
			ptr_uv2 = (float*)static_cast<uintptr_t>(jsonData["ptr_uv2"]);
			std::cout << "ptr_uv2: " << (uintptr_t)ptr_uv2 << std::endl;
		}
	}
	if (ptr_uv2 != nullptr) {
		this->num_uv2 = this->num_vertices;
		for (size_t i = 0; i < this->num_uv2; ++i) {
			std::vector<float> uv = { ptr_uv2[i * 2 + 0], ptr_uv2[i * 2 + 1] };
			this->UV_list2.emplace_back(uv);
		}
	}

	if (ptr_normals == nullptr) {
		if (jsonData.contains("ptr_normals")) {
			ptr_normals = (float*)static_cast<uintptr_t>(jsonData["ptr_normals"]);
			std::cout << "ptr_normals: " << (uintptr_t)ptr_normals << std::endl;
		}
		else {
			std::cout << "Error: 'normals' is null." << std::endl;
			return false;
		}
	}

	this->num_normals = this->num_vertices;
	for (size_t i = 0; i < this->num_normals; ++i) {
		float sqr = ptr_normals[i * 3 + 0] * ptr_normals[i * 3 + 0] + ptr_normals[i * 3 + 1] * ptr_normals[i * 3 + 1] + ptr_normals[i * 3 + 2] * ptr_normals[i * 3 + 2];
		float inv_norm = 1.0f / std::sqrt(sqr);
		std::vector<float> n = { ptr_normals[i * 3 + 0] * inv_norm, ptr_normals[i * 3 + 1] * inv_norm, ptr_normals[i * 3 + 2] * inv_norm };
		this->normals.emplace_back(n);
	}

	if (ptr_tangents == nullptr) {
		if (jsonData.contains("ptr_tangents")) {
			ptr_tangents = (float*)static_cast<uintptr_t>(jsonData["ptr_tangents"]);
			std::cout << "ptr_tangents: " << (uintptr_t)ptr_tangents << std::endl;
		}
		else {
			std::cout << "Error: 'tangents' is null." << std::endl;
			return false;
		}
	}

	if (ptr_bitangent_signs == nullptr) {
		if (jsonData.contains("ptr_bitangent_signs")) {
			ptr_bitangent_signs = (int32_t*)static_cast<uintptr_t>(jsonData["ptr_bitangent_signs"]);
			std::cout << "ptr_bitangent_signs: " << (uintptr_t)ptr_bitangent_signs << std::endl;
		}
		else {
			std::cout << "Error: 'bitangent_signs' is null." << std::endl;
			return false;
		}
	}

	this->num_tangents = this->num_vertices;
	for (size_t i = 0; i < this->num_tangents; ++i) {
		std::vector<float> t = { ptr_tangents[i * 3 + 0], ptr_tangents[i * 3 + 1], ptr_tangents[i * 3 + 2] };
		this->tangents.emplace_back(t);
		this->tangent_signs.emplace_back(ptr_bitangent_signs[i] < 0 ? 3 : 0);
	}

	if (ptr_color == nullptr) {
		if (jsonData.contains("ptr_color")) {
			ptr_color = (float*)static_cast<uintptr_t>(jsonData["ptr_color"]);
			std::cout << "ptr_color: " << (uintptr_t)ptr_color << std::endl;
		}
	}
	if (ptr_color != nullptr) {
		this->num_vert_colors = this->num_vertices;
		for (size_t i = 0; i < this->num_vert_colors; ++i) {
			mesh::vertex_color c;
			c.r = uint8_t(ptr_color[i * 4 + 0] * 255);
			c.g = uint8_t(ptr_color[i * 4 + 1] * 255);
			c.b = uint8_t(ptr_color[i * 4 + 2] * 255);
			c.a = uint8_t(ptr_color[i * 4 + 3] * 255);
			this->vert_colors.emplace_back(c);
		}
	}

	const json& weightData = jsonData["vertex_weights"];

	if (weightData.is_array()) {
		// Check if length of weightData is equal to the number of vertices
		if (weightData.size() > 0 && weightData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'vertex_weights' is not equal to the number of vertices." << std::endl;
			std::cout << "Length of 'vertex_weights': " << weightData.size() << std::endl;
			std::cout << "Number of vertices: " << this->num_vertices << std::endl;
			return false;
		}

		size_t num_bones = 0;
		for (const auto& vw : weightData) {
			if (vw.is_array()) {
				if (vw.size() > this->num_weightsPerVertex) {
					this->num_weightsPerVertex = vw.size();
				}
				for (auto& elem : vw) {
					if (elem[0] > num_bones) {
						num_bones = elem[0];
					}
				}
			}
		}
		num_bones += 1;

		this->num_weights = weightData.size() * this->num_weightsPerVertex;
		this->weight_indices.resize(num_bones);

		uint32_t vertex_index = 0;
		for (const auto& vw : weightData) {
			vertex_weight vw_l = new bone_binding[this->num_weightsPerVertex];
			memset(vw_l, 0, sizeof(bone_binding) * this->num_weightsPerVertex);

			std::vector<std::vector<double>> bb_raw;
			std::vector<std::vector<uint16_t>> bb_l;
			double sum_weight = 0;
			for (const auto& element : vw) {

				std::vector<double> bb_per_vert_per_bone_raw;


				for (const auto& e : element) {
					double _e = e;
					bb_per_vert_per_bone_raw.push_back(_e);
				}


				sum_weight += bb_per_vert_per_bone_raw[1];
				bb_per_vert_per_bone_raw[1] *= uint16_t(-1);

				bb_raw.emplace_back(bb_per_vert_per_bone_raw);
			}

			int _i = 0;
			for (auto& bb_per_vert_per_bone_raw : bb_raw) {
				uint16_t bone_id = bb_per_vert_per_bone_raw[0];
				uint16_t weight = 0;

				this->weight_indices[bone_id].push_back(vertex_index);

				uint16_t _Max = uint16_t(-1);
				if (options & Options::NormalizeWeight) {
					double _w = bb_per_vert_per_bone_raw[1] / sum_weight;

					// Make sure the weights is never going to overflow
					if (_w > _Max)
						weight = _Max;
					else if (_w < 0)
						weight = uint16_t(0);
					else
						weight = uint16_t(_w);

					_Max = _Max - weight;

				}
				else {
					weight = uint16_t(bb_per_vert_per_bone_raw[1]);
				}

				vw_l[_i].bone = bone_id;
				vw_l[_i].weight = weight;

				++_i;
			}

			this->weights.push_back(vw_l);
			vertex_index++;
		}
	}
	else {
		std::cout << "Error: 'vertex_weights' is not an array." << std::endl;
		return false;
	}

	std::cout << "Done loading mesh from numpy." << std::endl;

	return this->PostProcess(options);
}

bool mesh::MeshIO::LoadFromJson(const nlohmann::json& jsonData, const float scale_factor, const uint32_t options)
{
	if (!this->GeometryFromJson(jsonData, scale_factor)) {
		std::cout << "Error: Failed to load JSON file." << std::endl;
		return false;
	}

	const json& normalsData = jsonData["normals"];

	if (normalsData.is_array()) {
		// Check if length of normalsData is equal to the number of vertices
		if (normalsData.size() > 0 && normalsData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'normals' is not equal to the number of vertices." << std::endl;
			return false;
		}

		this->num_normals = normalsData.size();
		for (const auto& n : normalsData) {
			if (n.is_array()) {
				std::vector<float> n_l;
				float norm = 0;
				for (const auto& element : n) {
					if (element.is_number()) {
						float _n = element;
						n_l.push_back(_n);
						norm += _n * _n;
					}
				}
				norm = std::sqrt(norm);
				this->normals.push_back({ n_l[0] / norm, n_l[1] / norm, n_l[2] / norm });
			}
		}
	}
	else {
		std::cout << "Error: 'normals' is not an array." << std::endl;
		return false;
	}

	// Load tangents
	const json& tangentsData = jsonData["tangents"];

	if (tangentsData.is_array()) {
		// Check if length of tangentsData is equal to the number of vertices
		if (tangentsData.size() > 0 && tangentsData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'tangents' is not equal to the number of vertices." << std::endl;
			return false;
		}

		this->num_tangents = tangentsData.size();
		for (const auto& t : tangentsData) {
			if (t.is_array()) {
				std::vector<float> t_l{ t[0], t[1], t[2] };
				this->tangents.push_back(t_l);
				this->tangent_signs.push_back(t[3]);
			}
		}
	}
	else {
		std::cout << "Error: 'tangents' is not an array." << std::endl;
		return false;
	}

	const json& vertColorData = jsonData["vertex_color"];

	if (vertColorData.is_array()) {
		// Check if length of vertColorData is equal to the number of vertices
		if (vertColorData.size() > 0 && vertColorData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'vertex_color' is not equal to the number of vertices." << std::endl;
			return false;
		}

		this->num_vert_colors = vertColorData.size();
		for (const auto& vc : vertColorData) {
			if (vc.is_array()) {
				std::vector<uint8_t> vc_l;
				for (const auto& element : vc) {
					if (element.is_number()) {
						float _vc = element;
						vc_l.push_back(uint8_t(_vc * 255));
					}
				}
				this->vert_colors.push_back({ vc_l[0],vc_l[1],vc_l[2],vc_l[3] });
			}
		}
	}
	else {
		std::cout << "Error: 'vertex_color' is not an array." << std::endl;
		return false;
	}

	const json& weightData = jsonData["vertex_weights"];

	if (weightData.is_array()) {
		// Check if length of weightData is equal to the number of vertices
		if (weightData.size() > 0 && weightData.size() != this->num_vertices) {
			std::cout << "Error: Length of 'vertex_weights' is not equal to the number of vertices." << std::endl;
			std::cout << "Length of 'vertex_weights': " << weightData.size() << std::endl;
			std::cout << "Number of vertices: " << this->num_vertices << std::endl;
			return false;
		}

		size_t num_bones = 0;
		for (const auto& vw : weightData) {
			if (vw.is_array()) {
				if (vw.size() > this->num_weightsPerVertex) {
					this->num_weightsPerVertex = vw.size();
				}
				for (auto& elem : vw) {
					if (elem[0] > num_bones) {
						num_bones = elem[0];
					}
				}
			}
		}
		num_bones += 1;

		this->num_weights = weightData.size() * this->num_weightsPerVertex;
		this->weight_indices.resize(num_bones);

		uint32_t vertex_index = 0;
 		for (const auto& vw : weightData) {
			vertex_weight vw_l = new bone_binding[this->num_weightsPerVertex];
			memset(vw_l, 0, sizeof(bone_binding) * this->num_weightsPerVertex);

			std::vector<std::vector<double>> bb_raw;
			std::vector<std::vector<uint16_t>> bb_l;
			double sum_weight = 0;
			for (const auto& element : vw) {

				std::vector<double> bb_per_vert_per_bone_raw;


				for (const auto& e : element) {
					double _e = e;
					bb_per_vert_per_bone_raw.push_back(_e);
				}


				sum_weight += bb_per_vert_per_bone_raw[1];
				bb_per_vert_per_bone_raw[1] *= uint16_t(-1);

				bb_raw.emplace_back(bb_per_vert_per_bone_raw);
			}

			int _i = 0;
			for (auto& bb_per_vert_per_bone_raw : bb_raw) {
				uint16_t bone_id = bb_per_vert_per_bone_raw[0];
				uint16_t weight = 0;

				this->weight_indices[bone_id].push_back(vertex_index);

				uint16_t _Max = uint16_t(-1);
				if (options & Options::NormalizeWeight) {
					double _w = bb_per_vert_per_bone_raw[1] / sum_weight;

					// Make sure the weights is never going to overflow
					if (_w > _Max)
						weight = _Max;
					else if (_w < 0)
						weight = uint16_t(0);
					else
						weight = uint16_t(_w);

					_Max = _Max - weight;

				}
				else {
					weight = uint16_t(bb_per_vert_per_bone_raw[1]);
				}

				vw_l[_i].bone = bone_id;
				vw_l[_i].weight = weight;

				++_i;
			}

			this->weights.push_back(vw_l);
			vertex_index++;
		}
	}
	else {
		std::cout << "Error: 'vertex_weights' is not an array." << std::endl;
		return false;
	}

	const json& smoothGroupData = jsonData["smooth_group"];

	if (smoothGroupData.is_array()) {
		this->num_smooth_group = smoothGroupData.size();
		// Read indices from the smooth group data
		for (const auto& sg : smoothGroupData) {
			if (sg.is_number()) {
				this->smooth_group.push_back(sg);
			}
		}
	}
	else {
		std::cout << "Error: 'smooth_group' is not an array." << std::endl;
		return false;
	}

	std::cout << "Done loading mesh from string." << std::endl;

	return this->PostProcess(options);
}

bool mesh::MeshIO::LoadToNumpy(
	float* ptr_positions, 
	int32_t* ptr_indices,
	float* ptr_normals, 
	float* ptr_uv1, 
	float* ptr_uv2, 
	float* ptr_color, 
	float* ptr_tangents, 
	int32_t* ptr_bitangent_signs,
	float* ptr_weights,
	int32_t* ptr_bone_indices
) {
	if (ptr_positions != nullptr) {
		for (size_t i = 0; i < this->num_vertices; ++i) {
			ptr_positions[i * 3 + 0] = this->positions[i * 3 + 0];
			ptr_positions[i * 3 + 1] = this->positions[i * 3 + 1];
			ptr_positions[i * 3 + 2] = this->positions[i * 3 + 2];
		}
	}

	if (ptr_indices != nullptr) {
		for (size_t i = 0; i < this->indices_size; ++i) {
			ptr_indices[i] = this->indices[i];
		}
	}

	if (ptr_normals != nullptr) {
		for (size_t i = 0; i < this->num_vertices; ++i) {
			ptr_normals[i * 3 + 0] = this->normals[i][0];
			ptr_normals[i * 3 + 1] = this->normals[i][1];
			ptr_normals[i * 3 + 2] = this->normals[i][2];
		}
	}

	if (ptr_uv1 != nullptr) {
		for (size_t i = 0; i < this->num_uv1; ++i) {
			ptr_uv1[i * 2 + 0] = this->UV_list1[i][0];
			ptr_uv1[i * 2 + 1] = this->UV_list1[i][1];
		}
	}

	if (ptr_uv2 != nullptr && this->num_uv2 == this->num_uv1) {
		for (size_t i = 0; i < this->num_uv2; ++i) {
			ptr_uv2[i * 2 + 0] = this->UV_list2[i][0];
			ptr_uv2[i * 2 + 1] = this->UV_list2[i][1];
		}
	}

	if (ptr_color != nullptr) {
		for (size_t i = 0; i < this->num_vert_colors; ++i) {
			ptr_color[i * 4 + 0] = this->vert_colors[i].r / 255;
		}
	}

	if (ptr_tangents != nullptr) {
		for (size_t i = 0; i < this->num_tangents; ++i) {
			ptr_tangents[i * 3 + 0] = this->tangents[i][0];
			ptr_tangents[i * 3 + 1] = this->tangents[i][1];
			ptr_tangents[i * 3 + 2] = this->tangents[i][2];
		}
	}

	if (ptr_bitangent_signs != nullptr) {
		for (size_t i = 0; i < this->num_tangents; ++i) {
			ptr_bitangent_signs[i] = this->tangent_signs[i];
		}
	}

	if (ptr_weights != nullptr && ptr_bone_indices != nullptr) {
		for (size_t i = 0; i < this->num_vertices; ++i) {
			for (size_t j = 0; j < this->num_weightsPerVertex; ++j) {
				ptr_weights[i * this->num_weightsPerVertex + j] = this->weights[i][j].weight/65535.f;
				ptr_bone_indices[i * this->num_weightsPerVertex + j] = this->weights[i][j].bone;
			}
		}
	}

	return true;
}

bool mesh::MeshIO::SerializeToJsonStr(std::string& json_data) const
{
	json jsonData;

	if (!SerializeToJson(jsonData)) {
		return false;
	}

	// Write the json data to file
	json_data = jsonData.dump(4);

	return true;
}

bool mesh::MeshIO::SerializeToJson(nlohmann::json& jsonData) const
{
	std::string obj_content;

	WavefrontWriter wfw;
	if (!wfw.WriteString(obj_content, "DEFAULT", this->indices, this->positions, this->UV_list1, this->normals)) {
		return false;
	}

	jsonData["obj_content"] = obj_content;

	int tangents_count = 0;

	if (this->num_uv2 > 0) {
		json uv2Data = json::array();
		for (auto& uv2 : this->UV_list2) {
			json uv2_l = json::array();
			uv2_l.push_back(uv2[0]);
			uv2_l.push_back(uv2[1]);
			uv2Data.push_back(uv2_l);
		}
		jsonData["uv_coords2"] = uv2Data;
	}

	jsonData["max_border"] = this->max_border;

	json tangentsData = json::array();
	for (int i = 0; i < this->num_vertices; ++i) {
		auto& t = this->tangents[i];
		auto& s = this->tangent_signs[i];
		json t_l = json::array();
		t_l.push_back(t[0]);
		t_l.push_back(t[1]);
		t_l.push_back(t[2]);
		t_l.push_back(s);
		tangentsData.push_back(t_l);
		++tangents_count;
	}
	jsonData["tangents"] = tangentsData;

	// Save vertex colors in json format
	int vertex_color_count = 0;
	json vertColorData = json::array();
	for (auto vc : this->vert_colors) {
		json vc_l = json::array();
		vc_l.push_back(vc.r / 255.0f);
		vc_l.push_back(vc.g / 255.0f);
		vc_l.push_back(vc.b / 255.0f);
		vc_l.push_back(vc.a / 255.0f);
		vertColorData.push_back(vc_l);
		++vertex_color_count;
	}
	jsonData["vertex_color"] = vertColorData;

	// Save vertex weights in json format
	int vertex_weight_count = 0;
	json weightData = json::array();
	for (auto vw : this->weights) {
		json vw_l = json::array();
		for (int i = 0; i < this->num_weightsPerVertex; i++) {
			json vw_per_vert_per_bone_l = json::array();
			vw_per_vert_per_bone_l.push_back(vw[i].bone);
			if (vw[i].weight <= 1) {
				vw_per_vert_per_bone_l.push_back(0);
			}
			else {
				vw_per_vert_per_bone_l.push_back(vw[i].weight / 65535.f);
			}
			vw_l.push_back(vw_per_vert_per_bone_l);
		}
		weightData.push_back(vw_l);
		++vertex_weight_count;
	}
	jsonData["vertex_weights"] = weightData;

	// Save meshlets in json format
	int meshlet_count = 0;
	json meshletData = json::array();
	for (auto meshlet : this->meshlets) {
		json meshlet_l = json::array();
		meshlet_l.push_back(meshlet.VertCount);
		meshlet_l.push_back(meshlet.VertOffset);
		meshlet_l.push_back(meshlet.PrimCount);
		meshlet_l.push_back(meshlet.PrimOffset);
		meshletData.push_back(meshlet_l);
		++meshlet_count;
	}
	jsonData["meshlets"] = meshletData;

	// Save culldata in json format
	int culldata_count = 0;
	json culldata = json::array();
	for (auto cd : this->culldata) {
		json cd_l = json::array();
		cd_l.push_back(cd.center[0]);
		cd_l.push_back(cd.center[1]);
		cd_l.push_back(cd.center[2]);
		cd_l.push_back(cd.expand[0]);
		cd_l.push_back(cd.expand[1]);
		cd_l.push_back(cd.expand[2]);
		culldata.push_back(cd_l);
		++culldata_count;
	}
	jsonData["culldata"] = culldata;

	return true;
}

bool mesh::MeshIO::PostProcess(const uint32_t options)
{
	this->UpdateDXAttr();

	if (options & Options::DoOptimize) {
		Optimize(this->indices, DX_positions, DX_normals, DX_uvs, this->weights, this->vert_colors);
		this->UpdateAttrFromDX();
	}

	if ((options & Options::GenerateTangentIfNA) && this->tangents.empty()) {
		if (!this->GenerateTangents(options)) {
			std::cout << "Error: Failed to generate tangent vectors." << std::endl;
			return false;
		}
	}

	if (!this->GenerateMeshlets()) {
		std::cout << "Error: Failed to generate meshlets." << std::endl;
		return false;
	}

	return true;
}

void MeshIO::Clear()
{
	this->max_border = 1.0f;
	this->num_weightsPerVertex = 0;
	this->num_triangles = 0;
	this->num_positions = 0;
	this->num_vertices = 0;
	this->num_uv1 = 0;
	this->num_uv2 = 0;
	this->num_vert_colors = 0;
	this->num_normals = 0;
	this->num_tangents = 0;
	this->num_weights = 0;
	this->num_lods = 0;
	this->num_meshlets = 0;
	this->num_culldata = 0;
	this->num_smooth_group = 0;

	this->indices.clear();
	this->positions.clear();
	this->UV_list1.clear();
	this->UV_list2.clear();
	this->vert_colors.clear();
	this->normals.clear();
	this->tangents.clear();
	this->weights.clear();
	this->weight_indices.clear();
	this->bone_bounding.clear();
	this->meshlets.clear();
	this->culldata.clear();
	this->smooth_group.clear();

	this->indices_size = 0;

	this->DX_positions.clear();
	this->DX_normals.clear();
	this->DX_uvs.clear();

	return;
}

class com_exception : public std::exception
{
public:
	com_exception(HRESULT hr) : result(hr) {}

	virtual const char* what() const override
	{
		static char s_str[64] = {};
		sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
		return s_str;
	}

private:
	HRESULT result;
};

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
#ifdef _DEBUG
		char str[128] = {};
		sprintf_s(str, "**ERROR** Fatal Error with HRESULT of %08X\n", static_cast<unsigned int>(hr));
		OutputDebugStringA(str);
		__debugbreak();
#endif
		throw com_exception(hr);
	}
}

// Perform mesh cleaning and optimization. This function is largely taken from the DirectXMesh sample: 
// https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/Samples/Desktop/D3D12MeshShaders/src/WavefrontConverter/MeshProcessor.cpp
void MeshIO::Optimize(std::vector<uint16_t>&	a_indices,
		std::vector<XMFLOAT3>&					a_positions,
		std::vector<XMFLOAT3>&					a_normals,
		std::vector<XMFLOAT2>&					a_uvs,
		std::vector<vertex_weight>&				a_weights,
		std::vector<vertex_color>&		a_vertColors)
{
	std::unordered_map<size_t, uint32_t>    m_uniqueVertices;

	std::vector<uint32_t>                   m_faceRemap;
	std::vector<uint32_t>                   m_vertexRemap;
	std::vector<uint8_t>                    m_indexReorder;
	std::vector<uint32_t>                   m_dupVerts;
	std::vector<vertex_weight>				m_weightsReorder;
	std::vector<vertex_color>				m_vertColorsReorder;

	std::vector<DirectX::XMFLOAT3>          m_positionReorder;
	std::vector<DirectX::XMFLOAT3>          m_normalReorder;
	std::vector<DirectX::XMFLOAT2>          m_uvReorder;

	// Pull out some final counts for readability
	const uint32_t m_vertexCount = static_cast<uint32_t>(this->num_vertices);
	const uint32_t m_triCount = this->indices_size / 3;

	// Resize all our interim data buffers to appropriate sizes for the mesh
	m_positionReorder.resize(m_vertexCount);
	m_indexReorder.resize(kIndexByteCount * this->indices_size);

	m_faceRemap.resize(m_triCount);
	m_vertexRemap.resize(m_vertexCount);

	std::vector<uint32_t> DUMMY_attributes;
	DUMMY_attributes.resize(m_triCount, 0);

	std::vector<uint8_t> temp_indices;
	temp_indices.resize(kIndexByteCount * this->indices_size);
	std::memcpy(temp_indices.data(), a_indices.data(), this->indices_size * kIndexByteCount);


	///
	// Use DirectXMesh to optimize our vertex buffer data. 
	
	// Clean the mesh, sort faces by material, and reorder
	ThrowIfFailed(DirectX::Clean(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_vertexCount, nullptr, DUMMY_attributes.data(), m_dupVerts, true));
	ThrowIfFailed(DirectX::AttributeSort(m_triCount, DUMMY_attributes.data(), m_faceRemap.data()));
	ThrowIfFailed(DirectX::ReorderIB(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_faceRemap.data(), reinterpret_cast<uint16_t*>(m_indexReorder.data())));

	std::swap(temp_indices, m_indexReorder);

	// Optimize triangle faces and reorder
	ThrowIfFailed(DirectX::OptimizeFacesLRU(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_faceRemap.data()));
	ThrowIfFailed(DirectX::ReorderIB(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_faceRemap.data(), reinterpret_cast<uint16_t*>(m_indexReorder.data())));

	std::swap(temp_indices, m_indexReorder);

	// Optimize our vertex data
	ThrowIfFailed(DirectX::OptimizeVertices(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_vertexCount, m_vertexRemap.data()));

	// Finalize the index & vertex buffers (potential reordering)
	ThrowIfFailed(DirectX::FinalizeIB(reinterpret_cast<uint16_t*>(temp_indices.data()), m_triCount, m_vertexRemap.data(), m_vertexCount, reinterpret_cast<uint16_t*>(m_indexReorder.data())));
	ThrowIfFailed(DirectX::FinalizeVB(a_positions.data(), sizeof(XMFLOAT3), m_vertexCount, m_dupVerts.data(), m_dupVerts.size(), m_vertexRemap.data(), m_positionReorder.data()));

	std::swap(temp_indices, m_indexReorder);

	std::memcpy(a_indices.data(), temp_indices.data(), this->indices_size * kIndexByteCount);

	std::swap(a_positions, m_positionReorder);

	m_normalReorder.resize(m_vertexCount);
	ThrowIfFailed(DirectX::FinalizeVB(a_normals.data(), sizeof(XMFLOAT3), m_vertexCount, m_dupVerts.data(), m_dupVerts.size(), m_vertexRemap.data(), m_normalReorder.data()));

	std::swap(a_normals, m_normalReorder);

	m_uvReorder.resize(m_vertexCount);
	ThrowIfFailed(DirectX::FinalizeVB(a_uvs.data(), sizeof(XMFLOAT2), m_vertexCount, m_dupVerts.data(), m_dupVerts.size(), m_vertexRemap.data(), m_uvReorder.data()));

	std::swap(a_uvs, m_uvReorder);

	// Reorder the weights
	if (!a_weights.empty()) {
		m_weightsReorder.resize(m_vertexCount);
		ThrowIfFailed(DirectX::FinalizeVB(a_weights.data(), sizeof(vertex_weight), m_vertexCount, m_dupVerts.data(), m_dupVerts.size(), m_vertexRemap.data(), m_weightsReorder.data()));

		std::swap(a_weights, m_weightsReorder);
	}
	// Reorder the vertex colors
	if (!a_vertColors.empty()) {
		m_vertColorsReorder.resize(m_vertexCount);
		ThrowIfFailed(DirectX::FinalizeVB(a_vertColors.data(), sizeof(vertex_color), m_vertexCount, m_dupVerts.data(), m_dupVerts.size(), m_vertexRemap.data(), m_vertColorsReorder.data()));

		std::swap(a_vertColors, m_vertColorsReorder);
	}
}

void mesh::MeshIO::CalculateBoneBounding()
{
	typedef double FT;
	typedef Seb::Point<FT> Point;
	typedef std::vector<Point> PointVector;
	typedef Seb::Smallest_enclosing_ball<FT> Miniball;

	this->bone_bounding.clear();

#ifdef _DEBUG
	// Print weight_indices
	/*uint32_t bone_id = 0;
	for (auto& indices : this->weight_indices) {
		std::cout << "Bone: " << bone_id++ << std::endl;
		for (auto& index : indices) {
			std::cout << index << " ";
		}
		std::cout << std::endl;
	}*/
#endif


	for (auto& indices : this->weight_indices) {
		if (indices.size() < 1) {
			bone_bounding.emplace_back(BoneBoundingSphere());
			std::cout << "Warning: Bone has zero vertex." << std::endl;
			continue;
		}
		else if (indices.size() == 1) {
			auto bounding_sphere = BoneBoundingSphere();
			bounding_sphere.center[0] = this->positions[indices[0] * 3];
			bounding_sphere.center[1] = this->positions[indices[0] * 3 + 1];
			bounding_sphere.center[2] = this->positions[indices[0] * 3 + 2];
			bounding_sphere.radius = 0.001;
			bone_bounding.emplace_back(bounding_sphere);
		}

		PointVector point_set;

		std::vector<double> coords(3);
		for (auto& index : indices) {
			coords[0] = this->positions[index * 3];
			coords[1] = this->positions[index * 3 + 1];
			coords[2] = this->positions[index * 3 + 2];
			point_set.push_back(Point(3, coords.begin()));
		}

		Miniball mb(3, point_set);

		BoneBoundingSphere bbs;
		bbs.center[0] = mb.center_begin()[0];
		bbs.center[1] = mb.center_begin()[1];
		bbs.center[2] = mb.center_begin()[2];
		bbs.radius = mb.radius();

		this->bone_bounding.emplace_back(bbs);
	}

#ifdef _DEBUG
	// Print bone_bounding
	/*for (auto& bb : this->bone_bounding) {
		std::cout << "Center: " << bb.center[0] << " " << bb.center[1] << " " << bb.center[2] << std::endl;
		std::cout << "Radius: " << bb.radius << std::endl;
	}*/
#endif

}

void MeshIO::UpdateDXAttr()
{
	// Convert positions into DX_positions
	DX_positions.clear();
	DX_positions.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		DX_positions[j].x = positions[j * 3];
		DX_positions[j].y = positions[j * 3 + 1];
		DX_positions[j].z = positions[j * 3 + 2];
	}

	DX_normals.clear();
	DX_normals.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		DX_normals[j].x = normals[j][0];
		DX_normals[j].y = normals[j][1];
		DX_normals[j].z = normals[j][2];
	}

	DX_uvs.clear();
	DX_uvs.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		DX_uvs[j].x = UV_list1[j][0];
		DX_uvs[j].y = UV_list1[j][1];
	}
}

void MeshIO::UpdateAttrFromDX()
{
	// Convert DX_positions into positions
	positions.clear();
	positions.resize(this->num_vertices * 3);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		positions[j * 3] = DX_positions[j].x;
		positions[j * 3 + 1] = DX_positions[j].y;
		positions[j * 3 + 2] = DX_positions[j].z;
	}
	// Convert DX_normals into normals
	normals.clear();
	normals.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		normals[j] = std::vector<float>{ DX_normals[j].x,DX_normals[j].y,DX_normals[j].z };
	}
	// Convert DX_uvs into UV_list1
	UV_list1.clear();
	UV_list1.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		UV_list1[j] = std::vector<float>{ DX_uvs[j].x,DX_uvs[j].y };
	}
}

bool MeshIO::GenerateTangents(const uint32_t& options) {
	XMFLOAT4* DX_tangents;
	//XMFLOAT3* DX_tangents3;
	XMFLOAT3* DX_bitangents;

	DX_tangents = new XMFLOAT4[this->num_vertices];
	//DX_tangents3 = new XMFLOAT3[this->num_vertices];
	DX_bitangents = new XMFLOAT3[this->num_vertices];
	/*if (FAILED(ComputeTangentFrame(this->indices.data(), this->num_triangles,
		DX_positions.data(), DX_normals.data(),
		DX_uvs.data(), this->num_vertices,
		DX_tangents, DX_bitangents)))
	{
		std::cout << "Error: Failed to generate tangents for the mesh." << std::endl;
		return false;
	}*/

	utils::ComputeTangentFrameImpl(this->num_vertices,this->num_triangles, this->indices.data(),
		reinterpret_cast<float*>(DX_positions.data()),
		reinterpret_cast<float*>(DX_uvs.data()),
		reinterpret_cast<float*>(DX_normals.data()),
		reinterpret_cast<float*>(DX_tangents),
		reinterpret_cast<float*>(DX_bitangents));

	this->tangents.clear();
	this->tangents.resize(this->num_vertices);

	if (options & Options::FlipTangent) {
		/*for (size_t j = 0; j < this->num_vertices; ++j) {
			this->tangents[j].push_back(DX_tangents[j].x * DX_tangents[j].w);
			this->tangents[j].push_back(DX_tangents[j].y * DX_tangents[j].w);
			this->tangents[j].push_back(DX_tangents[j].z * DX_tangents[j].w);
		}*/
	}
	else {
		for (size_t j = 0; j < this->num_vertices; ++j) {
			this->tangents[j].push_back(DX_tangents[j].x /** DX_tangents[j].w*/);
			this->tangents[j].push_back(DX_tangents[j].y /** DX_tangents[j].w*/);
			this->tangents[j].push_back(DX_tangents[j].z /** DX_tangents[j].w*/);
			this->tangent_signs[j] = DX_tangents[j].w == 1? 0 : 3;
		}
		/*for (size_t j = 0; j < this->num_vertices; ++j) {
			this->tangents[j].push_back(DX_tangents[j].x);
			this->tangents[j].push_back(DX_tangents[j].y);
			this->tangents[j].push_back(DX_tangents[j].z);
		}*/
	}
	this->num_tangents = this->tangents.size();

	return true;
}

bool MeshIO::GenerateMeshlets() {
	size_t max_vertices = 96; // 96 vertices per meshlet
	size_t max_prims = 128; // 96 primitives per meshlet

	std::vector<Meshlet>& meshlets = this->meshlets;
	meshlets.clear();
	std::vector<uint8_t> uniqueVertexIB;
	std::vector<MeshletTriangle> primitiveIndices;

	if (FAILED(ComputeMeshlets(indices.data(), this->num_triangles,
		DX_positions.data(), this->num_vertices,
		nullptr,
		meshlets, uniqueVertexIB, primitiveIndices, max_vertices, max_prims)))
	{
		std::cout << "Error: Failed to generate meshlets for the mesh." << std::endl;
		return false;
	}

	this->num_meshlets = this->meshlets.size();

	auto uniqueVertexIndices = reinterpret_cast<const uint16_t*>(uniqueVertexIB.data());
	size_t vertIndices = uniqueVertexIB.size() / sizeof(uint16_t);

	std::vector<uint16_t> uniqueVertexIndices_l;
	uniqueVertexIndices_l.resize(vertIndices);
	std::memcpy(uniqueVertexIndices_l.data(), uniqueVertexIndices, vertIndices * sizeof(uint16_t));

	// Convert meshlet triangles to normal triangles
	std::vector<uint16_t> indices_l;
	std::vector<std::vector<float>> meshlet_centers;
	std::vector<std::vector<float>> meshlet_expands;

	for (auto& _mesh_let : meshlets) {

		std::vector<float> xs, ys, zs;
		for (int i = 0; i < _mesh_let.PrimCount; i++) {
			uint16_t id0 = uniqueVertexIndices[_mesh_let.VertOffset + primitiveIndices[_mesh_let.PrimOffset + i].i0];
			uint16_t id1 = uniqueVertexIndices[_mesh_let.VertOffset + primitiveIndices[_mesh_let.PrimOffset + i].i1];
			uint16_t id2 = uniqueVertexIndices[_mesh_let.VertOffset + primitiveIndices[_mesh_let.PrimOffset + i].i2];
			indices_l.push_back(id0);
			indices_l.push_back(id1);
			indices_l.push_back(id2);
			
			xs.emplace_back(DX_positions[id0].x);
			xs.emplace_back(DX_positions[id1].x);
			xs.emplace_back(DX_positions[id2].x);

			ys.emplace_back(DX_positions[id0].y);
			ys.emplace_back(DX_positions[id1].y);
			ys.emplace_back(DX_positions[id2].y);

			zs.emplace_back(DX_positions[id0].z);
			zs.emplace_back(DX_positions[id1].z);
			zs.emplace_back(DX_positions[id2].z);
		}

		float min_x = *std::min_element(xs.begin(), xs.end());
		float max_x = *std::max_element(xs.begin(), xs.end());
		float min_y = *std::min_element(ys.begin(), ys.end());
		float max_y = *std::max_element(ys.begin(), ys.end());
		float min_z = *std::min_element(zs.begin(), zs.end());
		float max_z = *std::max_element(zs.begin(), zs.end());

		std::vector<float> center = { (min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2 };
		std::vector<float> expand = { max_x - center[0], max_y - center[1], max_z - center[2] };

		meshlet_centers.emplace_back(center);
		meshlet_expands.emplace_back(expand);
	}
	
	std::swap(this->indices, indices_l);


	std::vector<BSCullData>& cull = this->culldata;
	cull.clear();
	cull.resize(meshlets.size());

	/*if (FAILED(ComputeCullData(DX_positions.data(), this->num_vertices,
		meshlets.data(), meshlets.size(),
		uniqueVertexIndices, vertIndices,
		primitiveIndices.data(), primitiveIndices.size(), cull.data())))
	{
		std::cout << "Error: Failed to generate cull data for the mesh." << std::endl;
		return false;
	}*/

	for (size_t i = 0; i < this->num_meshlets; ++i) {
		memcpy(cull[i].center, meshlet_centers[i].data(), sizeof(float) * 3);
		memcpy(cull[i].expand, meshlet_expands[i].data(), sizeof(float) * 3);
	}

	this->num_culldata = this->culldata.size();

	// Mock up PrimOffset in meshlets
	uint32_t prev_primOffset = 0;
	uint32_t prev_primCount = 0;
	for (size_t i = 0; i < this->num_meshlets; ++i) {
		meshlets[i].PrimOffset = prev_primOffset + ((3 * prev_primCount + 3) & ~3);
		prev_primOffset = meshlets[i].PrimOffset;
		prev_primCount = meshlets[i].PrimCount;
	}

	return true;
}

size_t mesh::MeshIO::NaiveEdgeSmooth()
{
	// convert std::vector<double> to std::vector<float>
	std::vector<float> positions_f;
	positions_f.resize(this->num_vertices * 3);
	std::vector<float> normals_f;
	normals_f.resize(this->normals.size() * 3);

	if (this->num_smooth_group != 0) {
		for (size_t i: this->smooth_group) {
			positions_f[i * 3] = float(utils::double_to_snorm(this->positions[i * 3], this->max_border));
			positions_f[i * 3 + 1] = float(utils::double_to_snorm(this->positions[i * 3 + 1], this->max_border));
			positions_f[i * 3 + 2] = float(utils::double_to_snorm(this->positions[i * 3 + 2], this->max_border));
		}
		for (size_t i: this->smooth_group) {
			normals_f[i * 3] = this->normals[i][0];
			normals_f[i * 3 + 1] = this->normals[i][1];
			normals_f[i * 3 + 2] = this->normals[i][2];
		}
	}
	else {
		for (size_t i = 0; i < this->num_vertices; ++i) {
			positions_f[i * 3] = float(utils::double_to_snorm(this->positions[i * 3], this->max_border));
			positions_f[i * 3 + 1] = float(utils::double_to_snorm(this->positions[i * 3 + 1], this->max_border));
			positions_f[i * 3 + 2] = float(utils::double_to_snorm(this->positions[i * 3 + 2], this->max_border));
		}
		for (size_t i = 0; i < this->normals.size(); ++i) {
			normals_f[i * 3] = this->normals[i][0];
			normals_f[i * 3 + 1] = this->normals[i][1];
			normals_f[i * 3 + 2] = this->normals[i][2];
		}
	}

	auto merged  = array_ops::normalizeByAttributes(positions_f, normals_f);

	if (this->num_smooth_group != 0) {
		// convert std::vector<float> back to std::vector<std::vector<float>>
		for (size_t i: this->smooth_group) {
			this->normals[i][0] = normals_f[i * 3];
			this->normals[i][1] = normals_f[i * 3 + 1];
			this->normals[i][2] = normals_f[i * 3 + 2];
		}
	}
	else {
		for (size_t i = 0; i < this->normals.size(); ++i) {
			this->normals[i][0] = normals_f[i * 3];
			this->normals[i][1] = normals_f[i * 3 + 1];
			this->normals[i][2] = normals_f[i * 3 + 2];
		}
	}

	return merged;
}

bool mesh::MeshIO::read_header(const std::string filename, std::string& header_str)
{
	// Check file extension, return false if extension is not .mesh
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "mesh")
	{
		return false;
	}

	// Open the file
	std::ifstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		return false;
	}

	uint32_t magic = utils::read<uint32_t>(file)[0];
	/*if (magic != 1) {
		return false;
	}*/

	uint32_t indices_size = utils::read<uint32_t>(file)[0];

	auto num_triangles = indices_size / 3;


	// Skip indices_size * uint16_t bytes
	file.seekg(indices_size * sizeof(uint16_t), std::ios::cur);

	auto max_border = utils::read<float>(file)[0];

	auto num_weightsPerVertex = utils::read<uint32_t>(file)[0];

	auto num_vertices = utils::read<uint32_t>(file)[0];

	nlohmann::json json_data;

	json_data["indices_size"] = indices_size;
	json_data["num_triangles"] = num_triangles;
	json_data["max_border"] = max_border;
	json_data["num_weightsPerVertex"] = num_weightsPerVertex;
	json_data["num_vertices"] = num_vertices;

	header_str = json_data.dump();
	
	return true;
}
