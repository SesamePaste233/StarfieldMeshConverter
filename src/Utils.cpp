#include "Utils.h"

const wchar_t* utils::charToWchar(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbsrtowcs_s(nullptr, wc, cSize, &c, cSize, nullptr);

	return wc;
}

const char* utils::make_copy(std::string str)
{
	char* cstr = new char[str.length() + 1];
	std::memcpy(cstr, str.c_str(), str.length() + 1);
	return cstr;
}

uint32_t utils::encodeCRC32(const std::string& str)
{
	uint32_t crc = 0U;
	for (unsigned char c : str)
	{
		for (int k = 0; k < 8; k++, c = c >> 1)
			crc = (crc >> 1) ^ ((0U - ((crc ^ c) & 1U)) & 0xEDB88320U);
	}
	return crc;
}

std::vector<float> utils::decodeDEC3N_CHECK(uint32_t n, uint8_t _check_w)
{
	if (n == 0)
		return { 0,0,0 };

	float x, y, z, w;
	x = ((n & 1023) / 511.5) - 1.0;

	y = (((n >> 10) & 1023) / 511.5) - 1.0;

	z = (((n >> 20) & 1023) / 511.5) - 1.0;

	w = (n >> 30) & 0b11;

	if (w != _check_w) {
		std::cout << w << std::endl;
		throw 2;
	}

	return { x,y,z };
}

std::vector<float> utils::decodeDEC3N(uint32_t n)
{
	float x, y, z, w;
	x = ((n & 1023) / 511.5) - 1.0;

	y = (((n >> 10) & 1023) / 511.5) - 1.0;

	z = (((n >> 20) & 1023) / 511.5) - 1.0;

	w = (n >> 30) & 0b11;

	return { x,y,z };
}

std::vector<float> utils::decodeDEC3N_w(uint32_t n, float& w)
{
	float x, y, z;
	x = ((n & 1023) / 511.5) - 1.0;

	y = (((n >> 10) & 1023) / 511.5) - 1.0;

	z = (((n >> 20) & 1023) / 511.5) - 1.0;

	w = (n >> 30) & 0b11;

	return { x,y,z };
}

std::uint32_t utils::encodeDEC3N(const std::vector<float>& values, float w)
{

	std::uint32_t n = 0;
	n |= static_cast<std::uint32_t>((values[0] + 1.0f) * 511.5f) & 1023;
	n |= (static_cast<std::uint32_t>((values[1] + 1.0f) * 511.5f) & 1023) << 10;
	n |= (static_cast<std::uint32_t>((values[2] + 1.0f) * 511.5f) & 1023) << 20;

	// Add the encoded 'w' value (default is 1).
	n |= (uint8_t)w << 30;

	return n;
}

std::uint16_t utils::encodeRGB565(uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t rgb565 = 0;

	rgb565 |= (r >> 3) << 11;
	rgb565 |= (g >> 2) << 5;
	rgb565 |= (b >> 3) << 0;

	return rgb565;
}

void utils::decodeRGB565(uint16_t rgb565, uint8_t& r, uint8_t& g, uint8_t& b)
{
	r = (rgb565 >> 11) << 3;
	g = ((rgb565 >> 5) & 0x3F) << 2;
	b = (rgb565 & 0x1F) << 3;
}

float utils::halfToFloat(uint16_t halfFloat)
{
	// Define masks for extracting different parts of the half-precision float.
	uint16_t signBitMask = 0x8000;
	uint16_t exponentBitMask = 0x7C00;
	uint16_t fractionBitMask = 0x03FF;

	// Extract the sign, exponent, and fraction bits.
	uint16_t sign = (halfFloat & signBitMask) >> 15;
	uint16_t exponent = (halfFloat & exponentBitMask) >> 10;
	uint16_t fraction = halfFloat & fractionBitMask;

	// Handle special cases: NaN and infinity.
	if (exponent == 0x1F) {
		if (fraction == 0) {
			// If fraction bits are all zero, it's either positive or negative infinity.
			return (sign == 0) ? INFINITY : -INFINITY;
		}
		else {
			// Otherwise, it's a NaN (Not-a-Number) value.
			return NAN;
		}
	}

	// Calculate the components of the single-precision float.
	int32_t singleExponent = static_cast<int32_t>(exponent) - 15 + 127;
	int32_t singleFraction = static_cast<int32_t>(fraction) << 13;

	// Combine the sign, exponent, and fraction to form the single-precision float.
	uint32_t singleFloatBits = (sign << 31) | (singleExponent << 23) | singleFraction;

	// Use type punning to convert the bits to a float.
	float result;
	memcpy(&result, &singleFloatBits, sizeof(result));

	return result;
}

uint16_t utils::floatToHalf(float fullFloat)
{
	unsigned int x = *((unsigned int*)&fullFloat);
	unsigned int sign = x & 0x80000000;
	unsigned int exponent_f32 = (x & 0x7f800000) >> 23;
	unsigned int mantissa_f32 = x & 0x007fffff;
	unsigned short y = (unsigned short)(sign >> 16);
	unsigned int exponent_f16;
	unsigned int mantissa_f16;
	unsigned int hx;

	hx = x & 0x7fffffff;

	if (hx < 0x33800000) {
		return *((uint16_t*)&y);
	}
	if (hx > 0x7f800000) {
		y = 0x7e00;
		return *((uint16_t*)&y);
	}
	if (hx >= 0x477fffff) {
		y |= 0x7c00;
		return *((uint16_t*)&y);
	}

	mantissa_f16 = mantissa_f32 >> 13;

	if (exponent_f32 > 0x70) {
		exponent_f16 = exponent_f32 - 0x70;
	}
	else {
		exponent_f16 = 0;
		mantissa_f16 |= 0x400;
		mantissa_f16 = mantissa_f16 >> (0x71 - exponent_f32);
	}
	y = y | (unsigned short)(exponent_f16 << 10) | (unsigned short)mantissa_f16;
	return *((uint16_t*)&y);
}

void utils::writeStringToBuffer(uint8_t* buffer, size_t& offset, const std::string& value)
{
	std::memcpy(buffer + offset, value.c_str(), value.length());
	offset += value.length();
}

std::vector<float> utils::readHalfAsFull(std::istream& file, int counts, bool big_endian) {
	std::vector<float> result;
	result.reserve(counts);
	for (int i = 0; i < counts; ++i) {
		uint16_t value;
		file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
		if (big_endian) {
			value = switchEndian(value);
		}
		result.push_back(halfToFloat(value));
	}
	return result;
}

std::string utils::readString(std::istream& file, int counts)
{
	std::string result;
	result.reserve(counts);
	for (int i = 0; i < counts; ++i) {
		char value;
		file.read(reinterpret_cast<char*>(&value), sizeof(char));
		result.push_back(value);
	}
	return result;
}

const uint8_t* utils::readBytes(std::istream& file, size_t bytes)
{
	uint8_t* buffer = new uint8_t[bytes];
	file.read(reinterpret_cast<char*>(buffer), bytes);
	return buffer;
}

float utils::readHalfAsFullFromBuffer(const uint8_t* buffer, size_t& offset, bool big_endian)
{
	uint16_t value = *reinterpret_cast<const uint16_t*>(buffer + offset);
	offset += sizeof(uint16_t);
	if (big_endian) {
		value = switchEndian(value);
	}
	return halfToFloat(value);
}

std::string utils::readStringFromBuffer(const uint8_t* buffer, size_t& offset, size_t length)
{
	std::string value;
	value.reserve(length);
	for (int i = 0; i < length; ++i) {
		char c = buffer[offset + i];
		value.push_back(c);
	}
	offset += length;
	return value;
}

void utils::writeString(std::ostream& file, const std::string& value)
{
	file.write(value.c_str(), value.size());
}

uint32_t utils::binary_count(uint32_t n)
{
	uint32_t count = 0;
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}

uint32_t utils::binary_count(uint32_t* n, uint32_t length)
{
	uint32_t count = 0;
	for (int i = 0; i < length; i++) {
		count += binary_count(n[i]);
	}
	return count;
}

std::vector<uint32_t> utils::binary_positions(uint32_t n) {
	std::vector<uint32_t> positions;
	uint32_t count = 0;
	while (n) {
		if (n & 1) {
			positions.push_back(count);
		}
		count++;
		n >>= 1;
	}
	return positions;
}

std::vector<uint32_t> utils::binary_positions(uint32_t* n, uint32_t length)
{
	std::vector<uint32_t> positions;
	uint32_t count = 0;
	for (int i = 0; i < length; i++) {
		uint32_t _n = n[i];
		for (int j = 0; j < 32; j++) {
			if (_n & 1) {
				positions.push_back(count);
			}
			count++;
			_n >>= 1;
		}
	}
	return positions;
}

uint32_t* utils::positions_to_binary(std::vector<uint32_t> pos)
{
	_ASSERT(pos.size() <= 128);
	uint32_t* binary = new uint32_t[4];
	memset(binary, 0, 4 * sizeof(uint32_t));
	for (int i = 0; i < pos.size(); i++) {
		binary[pos[i] / 32] |= 1 << (pos[i] % 32);
	}
	return binary;
}

uint32_t* utils::fill_binary(uint32_t n)
{
	_ASSERT(n <= 128);
	uint32_t* binary = new uint32_t[4];
	memset(binary, 0, 4 * sizeof(uint32_t));
	for (int i = 0; i < n; i++) {
		binary[i / 32] |= 1 << (i % 32);
	}
	return binary;
}

size_t utils::getFilePaths(std::string _dir, std::vector<std::string>& _output, std::string extension)
{
	using namespace std::filesystem;
	for (const auto& entry : recursive_directory_iterator(_dir)) {
		if (is_regular_file(entry) && entry.path().extension() == extension) {
			_output.push_back(entry.path().string());
		}
	}
	return _output.size();
}

void utils::ComputeTangentFrameImpl(uint32_t vertex_count, uint32_t tri_count, uint16_t* indices, float* positions, float* UV, float* normals, float* tan, float* bit)
{
	memset(tan, 0, vertex_count * 4 * sizeof(float));
	memset(bit, 0, vertex_count * 3 * sizeof(float));

	for (int t = 0; t < tri_count; t++) {
		uint16_t* tri = indices + t * 3;

		int i1 = tri[0];
		int i2 = tri[1];
		int i3 = tri[2];

		float* v1 = positions + i1 * 3;
		float* v2 = positions + i2 * 3;
		float* v3 = positions + i3 * 3;

		float* w1 = UV + i1 * 2;
		float* w2 = UV + i2 * 2;
		float* w3 = UV + i3 * 2;

		auto pdx = _vector_subtract(v2, v1, 3);
		auto pdy = _vector_subtract(v3, v1, 3);

		auto tcdx = _vector_subtract(w2, w1, 2);
		auto tcdy = _vector_subtract(w3, w1, 2);

		float r = tcdx[0] * tcdy[1] - tcdy[0] * tcdx[1];

		r = r >= 0 ? 1 : -1;

		std::vector<float> _tdir{
			(tcdy[1] * pdx[0] - tcdx[1] * pdy[0]) * r,
			(tcdy[1] * pdx[1] - tcdx[1] * pdy[1]) * r,
			(tcdy[1] * pdx[2] - tcdx[1] * pdy[2]) * r
		};

		std::vector<float> _bdir{
			(tcdx[0] * pdy[0] - tcdy[0] * pdx[0]) * r,
			(tcdx[0] * pdy[1] - tcdy[0] * pdx[1]) * r,
			(tcdx[0] * pdy[2] - tcdy[0] * pdx[2]) * r
		};

		auto tdir = _vector_normalize(_tdir.data(), 3);
		auto bdir = _vector_normalize(_bdir.data(), 3);

		for (int j = 0; j < 3; j++) {
			int i = tri[j];

			_vector_addition_noalloc(tan + i * 4, tdir, 3);
			_vector_addition_noalloc(bit + i * 3, bdir, 3);
		}

		// free memory
		delete[] pdx;
		delete[] pdy;
		delete[] tcdx;
		delete[] tcdy;
		delete[] tdir;
		delete[] bdir;
	}

	float* zeros = new float[3] { 0, 0, 0 };
	for (int i = 0; i < vertex_count; i++) {
		float* n = normals + i * 3;

		float* t = tan + i * 4;
		float* b = bit + i * 3;


		if (memcmp(t, zeros, 3) == 0 || memcmp(b, zeros, 3) == 0) {
			t[0] = n[1]; t[1] = n[2]; t[2] = n[0];
			auto rtn = _vector_crossproduct(n, t);
			memcpy(b, rtn, 3 * sizeof(float));
			delete[] rtn;
		}
		else {
			_vector_normalize_noalloc(t, 3);
			auto rtn1 = _vector_multiply(n, _vector_dotproduct(n, t, 3), 3);
			auto bi = _vector_crossproduct(n, t);
			_vector_subtract_noalloc(t, rtn1, 3);
			_vector_normalize_noalloc(t, 3);
			delete[] rtn1;

			_vector_normalize_noalloc(b, 3);
			const float w = _vector_dotproduct(bi, b, 3);
			auto rtn2 = _vector_multiply(n, _vector_dotproduct(n, b, 3), 3);
			_vector_subtract_noalloc(b, rtn2, 3);
			auto rtn3 = _vector_multiply(t, _vector_dotproduct(t, b, 3), 3);
			_vector_subtract_noalloc(b, rtn3, 3);
			_vector_normalize_noalloc(b, 3);
			delete[] rtn2;
			delete[] rtn3;
			delete[] bi;

			t[3] = w < 0 ? -1.f : 1.f;
		}
	}
	delete[] zeros;
}

std::vector<double> utils::snorm_to_double(const std::vector<int16_t>& v, double s)
{
	std::vector<double> result;
	result.reserve(v.size());
	for (int16_t p : v) {
		result.emplace_back(snorm_to_double(p, s));
	}
	return result;
}

double utils::snorm_to_double(const int16_t p, double s)
{
	if (p < 0) {
		return (static_cast<double>(p) / 32768.0 * s);
	}
	else {
		return (static_cast<double>(p) / 32767.0 * s);
	}
}

int16_t utils::double_to_snorm(double value, double max_border)
{
	// Normalize the value to the range [-1, 1]
	value /= max_border;

	// Clamp the value to the range [-1, 1]
	if (value > 1) {
		value = 1;
	}
	else if (value < -1) {
		value = -1;
	}

	//value *= 0.9999; // This is to avoid rounding 1 to -1 or the other way around

	// Convert the normalized value to the snorm range and return as uint16_t
	if (value >= 0) {
		return static_cast<int16_t>(value * 32767.0);
	}
	else {
		return static_cast<int16_t>(value * 32768.0);
	}
}