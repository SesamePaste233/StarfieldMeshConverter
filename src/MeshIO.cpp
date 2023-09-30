#include "MeshIO.h"

using namespace DirectX;
using namespace mesh;

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

	// Load the mesh from the file
	uint32_t magic = Util::readUInt32(file)[0];
	if (magic != 1) {
		return false;
	}

	this->indices_size = Util::readUInt32(file)[0];

	this->num_triangles = indices_size / 3;

	for (int i = 0; i < indices_size; i++) {
		auto index = Util::readUInt16(file)[0];

		this->indices.emplace_back(index);
	}

	std::cout << std::hex << file.tellg() << std::endl;

	this->scale = Util::readFloat(file)[0];

	this->num_weightsPerVertex = Util::readUInt32(file)[0];


	std::cout << std::hex << file.tellg() << std::endl;

	this->num_vertices = Util::readUInt32(file)[0];

	this->num_positions = num_vertices * 3;

	for (int i = 0; i < num_positions; i++) {
		auto pos = Util::readInt16(file)[0];
		auto d = Util::snorm_to_double(pos, scale);
		auto r = Util::double_to_snorm(d, scale);

		this->positions.emplace_back(d);
	}

	// Get current position in file and display as hex
	std::cout << std::hex << file.tellg() << std::endl;

	this->num_uv1 = Util::readUInt32(file)[0];

	for (int i = 0; i < num_uv1; i++) {
		auto uv1 = Util::readHalfAsFull(file, 2);
		this->UV_list1.emplace_back(uv1);
	}
			
	this->num_uv2 = Util::readUInt32(file)[0];

	for (int i = 0; i < num_uv2; i++) {
		auto uv2 = Util::readHalfAsFull(file, 2);
		this->UV_list2.emplace_back(uv2);
	}

	this->num_vert_colors = Util::readUInt32(file)[0];

	for (int i = 0; i < num_vert_colors; i++) {
		auto color = Util::readUInt8(file, 4);
		this->vert_colors.push_back({ color[0],color[1],color[2],color[3] });
	}
			

	this->num_normals = Util::readUInt32(file)[0];

	for (int i = 0; i < num_normals; i++) {
		auto n = Util::readUInt32(file)[0];
		auto normal = Util::decodeUDEC3_2(n);
		this->normals.emplace_back(normal);
	}
	
	this->num_tangents = Util::readUInt32(file)[0];

	for (int i = 0; i < num_tangents; i++) {
		auto t = Util::readUInt32(file)[0];
		auto tangent = Util::decodeUDEC3_2(t);
		this->tangents.emplace_back(tangent);
	}

	this->num_weights = Util::readUInt32(file)[0];
	auto num_entries = this->num_vertices;

	for (int i = 0; i < num_entries; i++) {
		vertex_weight vw = new bone_binding[num_weightsPerVertex];

		for (int j = 0; j < num_weightsPerVertex; j++) {
			auto pair = Util::readUInt16(file, 2);
			vw[j].bone = pair[0];
			vw[j].weight = pair[1];
		}

		this->weights.emplace_back(vw);
	}

	this->unk_uint32_t = Util::readUInt32(file)[0];

	this->num_meshlets = Util::readUInt32(file)[0];

	for (int i = 0; i < num_meshlets; i++) {
		Meshlet ml;
		auto data = Util::readUInt32(file, 4);

		ml.VertCount = data[0];
		ml.VertOffset = data[1];
		ml.PrimCount = data[2];
		ml.PrimOffset = data[3];

		this->meshlets.emplace_back(ml);
	}

	this->num_culldata = Util::readUInt32(file)[0];
	for (int i = 0; i < num_meshlets; i++) {
		CullData cd;
		auto data = Util::readFloat(file, 4);
		cd.BoundingSphere.Center = XMFLOAT3(data[0], data[1], data[2]);
		cd.BoundingSphere.Radius = data[3];

		auto data2 = Util::readUInt32(file)[0];
		cd.NormalCone.v = data2;

		auto data3 = Util::readFloat(file)[0];
		cd.ApexOffset = data3;

		this->culldata.emplace_back(cd);
	}

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

	uint32_t magic = 1;
	Util::writeAsHex(file, magic);

	uint32_t dummy = 0;

	if (export_geometry) {
		this->indices_size = this->indices.size();
		Util::writeAsHex(file, this->indices_size);
		for (auto index : this->indices) {
			Util::writeAsHex(file, index);
		}

		Util::writeAsHex(file, this->scale);

		if (export_weights) {
			Util::writeAsHex(file, this->num_weightsPerVertex);
		}
		else {
			Util::writeAsHex(file, dummy);
		}

		this->num_vertices = this->positions.size() / 3;
		Util::writeAsHex(file, this->num_vertices);

		for (auto pos : this->positions) {
			auto p = Util::double_to_snorm(pos, this->scale);
			Util::writeAsHex(file, p);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
		Util::writeAsHex(file, this->scale);
		if (export_weights) {
			Util::writeAsHex(file, this->num_weightsPerVertex);
		}
		else {
			Util::writeAsHex(file, dummy);
		}
		Util::writeAsHex(file, dummy);
	}
	
	if (export_uvs) {
		this->num_uv1 = this->UV_list1.size();
		Util::writeAsHex(file, this->num_uv1);

		for (auto uv1 : this->UV_list1) {
			auto u = Util::floatToHalf(uv1[0]);
			auto v = Util::floatToHalf(uv1[1]);
			Util::writeAsHex(file, u);
			Util::writeAsHex(file, v);
		}

		this->num_uv2 = this->UV_list2.size();
		Util::writeAsHex(file, this->num_uv2);

		for (auto uv2 : this->UV_list2) {
			auto u = Util::floatToHalf(uv2[0]);
			auto v = Util::floatToHalf(uv2[1]);
			Util::writeAsHex(file, u);
			Util::writeAsHex(file, v);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
		Util::writeAsHex(file, dummy);
	}
	
	if (export_vert_colors) {
		this->num_vert_colors = this->vert_colors.size();
		Util::writeAsHex(file, this->num_vert_colors);

		for (auto color : this->vert_colors) {
			Util::writeAsHex(file, color.r);
			Util::writeAsHex(file, color.g);
			Util::writeAsHex(file, color.b);
			Util::writeAsHex(file, color.a);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}
	
	if (export_normals) {
		this->num_normals = this->normals.size();
		Util::writeAsHex(file, this->num_normals);

		for (auto normal : this->normals) {
			auto n = Util::encodeUDEC3_2(normal, 1);
			Util::writeAsHex(file, n);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}
	
	if(export_tangents){
		this->num_tangents = this->tangents.size();
		Util::writeAsHex(file, this->num_tangents);

		for (auto tangent : this->tangents) {
			auto t = Util::encodeUDEC3_2(tangent, 0);
			Util::writeAsHex(file, t);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}

	if (export_weights) {
		this->num_weights = this->weights.size();
		Util::writeAsHex(file, this->num_weights);

		for (auto vw : this->weights) {
			for (int j = 0; j < this->num_weightsPerVertex; j++) {
				Util::writeAsHex(file, vw[j].bone);
				Util::writeAsHex(file, vw[j].weight);
			}
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}

	Util::writeAsHex(file, this->unk_uint32_t);

	if (export_meshlets) {
		this->num_meshlets = this->meshlets.size();
		Util::writeAsHex(file, this->num_meshlets);

		for (auto meshlet : this->meshlets) {
			Util::writeAsHex(file, meshlet.VertCount);
			Util::writeAsHex(file, meshlet.VertOffset);
			Util::writeAsHex(file, meshlet.PrimCount);
			Util::writeAsHex(file, meshlet.PrimOffset);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}

	if (export_culldata) {
		this->num_culldata = this->culldata.size();
		Util::writeAsHex(file, this->num_culldata);

		for (auto culldata : this->culldata) {
			Util::writeAsHex(file, culldata.BoundingSphere.Center.x);
			Util::writeAsHex(file, culldata.BoundingSphere.Center.y);
			Util::writeAsHex(file, culldata.BoundingSphere.Center.z);
			Util::writeAsHex(file, culldata.BoundingSphere.Radius);
			Util::writeAsHex(file, culldata.NormalCone.v);
			Util::writeAsHex(file, culldata.ApexOffset);
		}
	}
	else {
		Util::writeAsHex(file, dummy);
	}

	return true;
}

using json = nlohmann::json;
bool MeshIO::Load(const std::string jsonBlenderFile, const float scale_factor, const bool generate_tangents_if_NA, const bool normalize_weight,const bool do_optimize) {
	this->Clear();

	std::ifstream file(jsonBlenderFile);
	if (!file.is_open()) {
		std::cout << "Error: Failed to open JSON file." << std::endl;
		return false;
	}

	json jsonData;
	file >> jsonData;
	file.close();

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

	this->scale = pos_max;

	if (this->num_vertices > uint16_t(-1)) {
		std::cout << "Error: Number of vertices has exceeded the maximum amount of 65535. Please split the mesh into smaller pieces before encoding." << std::endl;
		return false;
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
		std::cout<< "Error: 'vertex_indices_raw' is not an array." << std::endl;
		return false;
	}

	const json& normalsData = jsonData["normals"];

	if (normalsData.is_array()) {
		this->num_normals = normalsData.size();
		for (const auto& n : normalsData) {
			if (n.is_array()) {
				std::vector<float> n_l;
				for (const auto& element : n) {
					if (element.is_number()) {
						float _n = element;
						n_l.push_back(_n);
					}
				}
				this->normals.push_back(n_l);
			}
		}
	}
	else {
		std::cout << "Error: 'normals' is not an array." << std::endl;
		return false;
	}

	const json& UVData = jsonData["uv_coords"];

	if (UVData.is_array()) {
		this->num_uv1 = UVData.size();
		for (const auto& uv : UVData) {
			if (uv.is_array()) {
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

	const json& vertColorData = jsonData["vertex_color"];

	if (vertColorData.is_array()) {
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
		this->num_weights = weightData.size();
		for (const auto& vw : weightData) {
			if (vw.is_array()) {
				if (vw.size() > this->num_weightsPerVertex) {
					this->num_weightsPerVertex = vw.size();
				}
			}
		}
		for (const auto& vw : weightData) {
			vertex_weight vw_l = new bone_binding[this->num_weightsPerVertex];
			memset(vw_l, 0, sizeof(bone_binding)* this->num_weightsPerVertex);

			std::vector<std::vector<float>> bb_raw;
			std::vector<std::vector<uint16_t>> bb_l;
			double sum_weight = 0;
			for (const auto& element : vw) {

				std::vector<float> bb_per_vert_per_bone_raw;


				for (const auto& e : element) {
					float _e = e;
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

				if (normalize_weight) 
					weight = uint16_t(bb_per_vert_per_bone_raw[1] / sum_weight);
				else 
					weight = uint16_t(bb_per_vert_per_bone_raw[1]);

				vw_l[_i].bone = bone_id;
				vw_l[_i].weight = weight;

				++_i;
			}

			this->weights.push_back(vw_l);
			
		}
	}
	else {
		std::cout << "Error: 'vertex_weights' is not an array." << std::endl;
		return false;
	}

	this->UpdateDXAttr();

	if (do_optimize) {
		Optimize(this->indices, DX_positions, DX_normals, DX_uvs, this->weights, this->vert_colors);

		this->UpdateAttrFromDX();
	}

	if (generate_tangents_if_NA && this->tangents.empty()) {
		if (!this->GenerateTangents()) {
			return false;
		}
	}

	if (!this->GenerateMeshlets()) {
		return false;
	}
	
	return true;
}

void MeshIO::Clear()
{
	this->scale = 1.0f;
	this->num_weightsPerVertex = 0;
	this->num_triangles = 0;
	this->num_vertices = 0;
	this->num_uv1 = 0;
	this->num_uv2 = 0;
	this->num_vert_colors = 0;
	this->num_normals = 0;
	this->num_tangents = 0;
	this->num_weights = 0;
	this->unk_uint32_t = 0;
	this->num_meshlets = 0;
	this->num_culldata = 0;

	this->indices.clear();
	this->positions.clear();
	this->UV_list1.clear();
	this->UV_list2.clear();
	this->vert_colors.clear();
	this->normals.clear();
	this->tangents.clear();
	this->weights.clear();
	this->meshlets.clear();
	this->culldata.clear();

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
bool MeshIO::GenerateTangents() {
	std::vector<XMFLOAT4> DX_tangents;
	DX_tangents.resize(this->num_vertices);

	if (FAILED(ComputeTangentFrame(this->indices.data(), this->num_triangles,
		DX_positions.data(), DX_normals.data(),
		DX_uvs.data(), this->num_vertices,
		DX_tangents.data())))
	{
		std::cout << "Error: Failed to generate tangents for the mesh." << std::endl;
		return false;
	}
	this->tangents.clear();
	this->tangents.resize(this->num_vertices);
	for (size_t j = 0; j < this->num_vertices; ++j) {
		this->tangents[j].push_back(DX_tangents[j].x);
		this->tangents[j].push_back(DX_tangents[j].y);
		this->tangents[j].push_back(DX_tangents[j].z);
	}
}

bool MeshIO::GenerateMeshlets() {
	std::vector<Meshlet>& meshlets = this->meshlets;
	meshlets.clear();
	std::vector<uint8_t> uniqueVertexIB;
	std::vector<MeshletTriangle> primitiveIndices;
	if (FAILED(ComputeMeshlets(indices.data(), this->num_triangles,
		DX_positions.data(), this->num_vertices,
		nullptr,
		meshlets, uniqueVertexIB, primitiveIndices)))
	{
		std::cout << "Error: Failed to generate meshlets for the mesh." << std::endl;
		return false;
	}

	this->num_meshlets = this->meshlets.size();

	auto uniqueVertexIndices = reinterpret_cast<const uint16_t*>(uniqueVertexIB.data());
	size_t vertIndices = uniqueVertexIB.size() / sizeof(uint16_t);

	std::vector<CullData>& cull = this->culldata;
	cull.clear();
	cull.resize(meshlets.size());

	if (FAILED(ComputeCullData(DX_positions.data(), this->num_vertices,
		meshlets.data(), meshlets.size(),
		uniqueVertexIndices, vertIndices,
		primitiveIndices.data(), primitiveIndices.size(), cull.data())))
	{
		std::cout << "Error: Failed to generate cull data for the mesh." << std::endl;
		return false;
	}

	this->num_culldata = this->culldata.size();
}
