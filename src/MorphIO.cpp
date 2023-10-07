#include "MorphIO.h"

bool MorphIO::Deserialize(const std::string filename)
{
	// Check file extension, return false if extension is not .dat
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "dat")
	{
		std::cout << "Invalid file extension" << std::endl;
		return false;
	}

	// Open the file
	std::ifstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	// Read string of length 4
	auto head = Util::readString(file, 4);

	if (head != "MDAT"){
		std::cout << "Invalid file header" << std::endl;
		return false;
	}

	// Read unknown uint32_t
	this->num_axis = Util::readUInt32(file)[0];

	// Read number of vertices
	this->num_vertices = Util::readUInt32(file)[0];

	// Read number of entries
	this->num_shape_keys = Util::readUInt32(file)[0];

	for (int i = 0; i < this->num_shape_keys; i++) {
		uint32_t length_of_name = Util::readUInt32(file)[0];
		std::string name = Util::readString(file, length_of_name);
		this->morph_names.push_back(name);
	}

	// Print file pointer position in hex
	std::cout << std::hex << file.tellg() << std::endl;

	// Read number of rows
	this->num_morph_data = Util::readUInt32(file)[0];
	this->num_offsets = Util::readUInt32(file)[0];

	_ASSERT(num_vertices == num_offsets);

	for (int i = 0; i < this->num_morph_data; i++) {
		morph_data _morph_data;
		morph_data_hf _morph_data_hf;
		morph_data_sn _morph_data_sn;
		for (int j = 0; j < 8; j++) {
			_morph_data.v[j] = Util::readInt16(file)[0];
			_morph_data_hf.v[j] = Util::halfToFloat(_morph_data.v[j]);
			_morph_data_sn.v[j] = Util::snorm_to_double(_morph_data.v[j], 1.f);
		}
		this->morph_data_raw.push_back(_morph_data);
		this->morph_data_raw_hf.push_back(_morph_data_hf);
		this->morph_data_raw_sn.push_back(_morph_data_sn);
	}

	// Print file pointer position in hex
	std::cout << std::hex << file.tellg() << std::endl;

	for (int i = 0; i < this->num_offsets; i++) {
		IOffset _offset_data;
		_offset_data._offset = Util::readUInt32(file)[0];

		for (int j = 0; j < 4; j++) {
			_offset_data._marker[j] = static_cast<morph_key_selection>(Util::readUInt32(file)[0]);
		}

		this->offsets_list.push_back(_offset_data);
	}

	for (int i = 0; i < this->num_vertices; i++) {
		int t = this->offsets_list[i]._offset;
		int size = 0;
		if (i != this->num_vertices - 1)
			size = this->offsets_list[i + 1]._offset - this->offsets_list[i]._offset;
		else
			size = this->num_morph_data - this->offsets_list[i]._offset;

		std::vector<morph_data> _morph_data;

		std::vector<morph_data_hf> _morph_data_hf;

		std::vector<morph_data_sn> _morph_data_sn;

		std::vector<uint32_t> _morph_key_indices;

		_morph_key_indices = Util::binary_positions((uint32_t*)this->offsets_list[i]._marker, 4);

		for (int j = 0; j < size; j++) {
			_morph_data.push_back(this->morph_data_raw[t + j]);

			_morph_data_hf.push_back(this->morph_data_raw_hf[t + j]);

			_morph_data_sn.push_back(this->morph_data_raw_sn[t + j]);
		}

		this->per_vert_morph_data.push_back(_morph_data);

		this->per_vert_morph_data_hf.push_back(_morph_data_hf);

		this->per_vert_morph_data_sn.push_back(_morph_data_sn);

		this->per_vert_morph_key_indices.push_back(_morph_key_indices);
	}



    return false;
}
