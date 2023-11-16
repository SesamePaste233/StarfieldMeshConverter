#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <corecrt_wstring.h>
#include <chrono>
#include <limits>

// Eigen library
#include <Eigen/Dense>

class Util {
public:
	static const wchar_t* charToWchar(const char* c)
	{
		const size_t cSize = strlen(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbsrtowcs_s(nullptr, wc, cSize, &c, cSize, nullptr);

		return wc;
	}

	template<class T>
	inline static T switchEndian(const T& value) {
		T result = value;
		char* src = reinterpret_cast<char*>(&const_cast<T&>(value));
		char* dst = reinterpret_cast<char*>(&result) + sizeof(T) - 1;
		for (size_t i = 0; i < sizeof(T); ++i) {
			*dst-- = *src++;
		}
		return result;
	}

	static const char* make_copy(std::string str) {
		char* cstr = new char[str.length() + 1];
		std::memcpy(cstr, str.c_str(), str.length() + 1);
		return cstr;
	}

	// Credit goes to fo76utils. Original code: https://pastebin.com/e3TL3Q2m
	static uint32_t encodeCRC32(const std::string& str) {
		uint32_t crc = 0U;
		for (unsigned char c : str)
		{
			for (int k = 0; k < 8; k++, c = c >> 1)
				crc = (crc >> 1) ^ ((0U - ((crc ^ c) & 1U)) & 0xEDB88320U);
		}
		return crc;
	}

	static std::vector<float> decodeDEC3N_CHECK(uint32_t n, uint8_t _check_w) {
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

	static std::vector<float> decodeDEC3N(uint32_t n) {
		float x, y, z, w;
		x = ((n & 1023) / 511.5) - 1.0;

		y = (((n >> 10) & 1023) / 511.5) - 1.0;

		z = (((n >> 20) & 1023) / 511.5) - 1.0;

		w = (n >> 30) & 0b11;

		return { x,y,z };
	}

	static std::vector<float> decodeDEC3N_w(uint32_t n, float& w) {
		float x, y, z;
		x = ((n & 1023) / 511.5) - 1.0;

		y = (((n >> 10) & 1023) / 511.5) - 1.0;

		z = (((n >> 20) & 1023) / 511.5) - 1.0;

		w = (n >> 30) & 0b11;

		return { x,y,z };
	}

	static std::uint32_t encodeDEC3N(const std::vector<float>& values, float w) {

		std::uint32_t n = 0;
		n |= static_cast<std::uint32_t>((values[0] + 1.0f) * 511.5f) & 1023;
		n |= (static_cast<std::uint32_t>((values[1] + 1.0f) * 511.5f) & 1023) << 10;
		n |= (static_cast<std::uint32_t>((values[2] + 1.0f) * 511.5f) & 1023) << 20;

		// Add the encoded 'w' value (default is 1).
		n |= (uint8_t)w << 30;

		return n;
	}

	static float halfToFloat(uint16_t halfFloat) {
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

	static uint16_t floatToHalf(float fullFloat) {
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

	template<typename T>
	static void writeAsHex(std::ostream& file, T& value, bool big_endian = false) {
		T _v = value;
		if (big_endian) {
			_v = switchEndian(value);
		}
		file.write(reinterpret_cast<const char*>(&_v), sizeof(value));
	}

	static std::vector<float> readHalfAsFull(std::istream& file, int counts = 1, bool big_endian = false) {
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

	// Equivalent of readDouble in C++
	static std::vector<double> readDouble(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<double> result;
		result.reserve(8 * counts);
		for (int i = 0; i < 8 * counts; ++i) {
			double value;
			file.read(reinterpret_cast<char*>(&value), sizeof(double));
			if (big_endian) {
				value = switchEndian(value);
			}
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of snorm_to_double in C++
	static std::vector<double> snorm_to_double(const std::vector<int16_t>& v, double s) {
		std::vector<double> result;
		result.reserve(v.size());
		for (int16_t p : v) {
			result.emplace_back(snorm_to_double(p, s));
		}
		return result;
	}

	static double snorm_to_double(const int16_t p, double s) {
		if (p < 0) {
			return (static_cast<double>(p) / 32768.0 * s);
		}
		else {
			return (static_cast<double>(p) / 32767.0 * s);
		}
	}

	static int16_t double_to_snorm(double value, double max_border) {
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

	// Equivalent of readUInt32 in C++
	static std::vector<uint32_t> readUInt32(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<uint32_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint32_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
			if (big_endian) {
				value = switchEndian(value);
			}
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of readFloat in C++
	static std::vector<float> readFloat(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<float> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			float value;
			file.read(reinterpret_cast<char*>(&value), sizeof(float));
			if (big_endian) {
				value = switchEndian(value);
			}
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of readUInt8AsInt in C++
	static std::vector<uint8_t> readUInt8(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<uint8_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint8_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of readUInt16 in C++
	static std::vector<uint16_t> readUInt16(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<uint16_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint16_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
			if (big_endian) {
				value = switchEndian(value);
			}
			result.push_back(value);
		}
		return result;
	}

	static std::vector<int16_t> readInt16(std::istream& file, int counts = 1, bool big_endian = false) {
		std::vector<int16_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			int16_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(int16_t));
			if (big_endian) {
				value = switchEndian(value);
			}
			result.push_back(value);
		}
		return result;
	}

	static std::string readString(std::istream& file, int counts = 1) {
		std::string result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			char value;
			file.read(reinterpret_cast<char*>(&value), sizeof(char));
			result.push_back(value);
		}
		return result;
	}

	static const uint8_t* readBytes(std::istream& file, size_t bytes) {
		uint8_t* buffer = new uint8_t[bytes];
		file.read(reinterpret_cast<char*>(buffer), bytes);
		return buffer;
	}

	template<class T>
	static T readFromBuffer(const uint8_t* buffer, size_t& offset, bool big_endian = false) {
		T value;
		std::memcpy(&value, buffer + offset, sizeof(T));
		if (big_endian) {
			value = switchEndian(value);
		}
		offset += sizeof(T);
		return value;
	}

	static std::string readStringFromBuffer(const uint8_t* buffer, size_t& offset, size_t length) {
		std::string value;
		value.reserve(length);
		for (int i = 0; i < length; ++i) {
			char c = buffer[offset + i];
			value.push_back(c);
		}
		offset += length;
		return value;
	}

	static void writeString(std::ostream& file, const std::string& value) {
		file.write(value.c_str(), value.size());
	}

	template<class T>
	static void writeStream(std::ostream& file, const T* buffer, const size_t bytes) {
		file.write(reinterpret_cast<const char*>(buffer), bytes);
	}

	static uint32_t binary_count(uint32_t n) {
		uint32_t count = 0;
		while (n) {
			count += n & 1;
			n >>= 1;
		}
		return count;
	}

	static uint32_t binary_count(uint32_t* n, uint32_t length) {
		uint32_t count = 0;
		for (int i = 0; i < length; i++) {
			count += binary_count(n[i]);
		}
		return count;
	}

	static std::vector<uint32_t> binary_positions(uint32_t n) {
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

	static std::vector<uint32_t> binary_positions(uint32_t* n, uint32_t length) {
		std::vector<uint32_t> positions;
		uint32_t count = 0;
		for (int i = 0; i < length; i++) {
			uint32_t _n = n[i];
			for (int j = 0; j<32; j++) {
				if (_n & 1) {
					positions.push_back(count);
				}
				count++;
				_n >>= 1;
			}
		}
		return positions;
	}

	static size_t getFilePaths(std::string _dir, std::vector<std::string>& _output, std::string extension) {
		using namespace std::filesystem;
		for (const auto& entry : recursive_directory_iterator(_dir)) {
			if (is_regular_file(entry) && entry.path().extension() == extension) {
				_output.push_back(entry.path().string());
			}
		}
		return _output.size();
	}

	static uint32_t* positions_to_binary(std::vector<uint32_t> pos) {
		_ASSERT(pos.size() <= 128);
		uint32_t* binary = new uint32_t[4];
		memset(binary, 0, 4 * sizeof(uint32_t));
		for (int i = 0; i < pos.size(); i++) {
			binary[pos[i] / 32] |= 1 << (pos[i] % 32);
		}
		return binary;
	}

	static uint32_t* fill_binary(uint32_t n) {
		_ASSERT(n <= 128);
		uint32_t* binary = new uint32_t[4];
		memset(binary, 0, 4 * sizeof(uint32_t));
		for (int i = 0; i < n; i++) {
			binary[i / 32] |= 1 << (i % 32);
		}
		return binary;
	}
	template<class T>
	static T* _vector_subtract_noalloc(T* a, T* b, size_t length) {
		for (int i = 0; i < length; i++) {
			a[i] = a[i] - b[i];
		}
		return a;
	}

	template<class T>
	static T* _vector_subtract(T* a, T* b, size_t length) {
		T* result = new T[length];
		for (int i = 0; i < length; i++) {
			result[i] = a[i] - b[i];
		}
		return result;
	}

	template<class T>
	static void _vector_addition_noalloc(T* a, T* b, size_t length) {
		for (int i = 0; i < length; i++) {
			a[i] = a[i] + b[i];
		}
		return;
	}

	template<class T>
	static T _vector_norm(T* a, size_t length) {
		T sum = 0;
		for (int i = 0; i < length; i++) {
			sum += a[i] * a[i];
		}
		return sqrt(sum);
	}

	template<class T>
	static T* _vector_normalize(T* a, size_t length) {
		T* result = new T[length];
		T sum = 0;
		for (int i = 0; i < length; i++) {
			sum += a[i] * a[i];
		}
		T inv_sum = _fast_inv_sqrt(sum);
		for (int i = 0; i < length; i++) {
			result[i] = a[i] * inv_sum;
		}
		return result;
	}

	template<class T>
	static void _vector_normalize_noalloc(T* a, size_t length) {
		T sum = 0;
		for (int i = 0; i < length; i++) {
			sum += a[i] * a[i];
		}
		T inv_sum = _fast_inv_sqrt(sum);
		for (int i = 0; i < length; i++) {
			a[i] = a[i] * inv_sum;
		}
		return;
	}

	template<class T>
	static T _vector_dotproduct(T* a, T* b, size_t length) {
		T sum = 0;
		for (int i = 0; i < length; i++) {
			sum += a[i] * b[i];
		}
		return sum;
	}

	template<class T>
	static void _vector_multiply_noalloc(T* a, T b, size_t length) {
		for (int i = 0; i < length; i++) {
			a[i] = a[i] * b;
		}
		return;
	}
	template<class T>
	static T* _vector_multiply(T* a, T b, size_t length) {
		T* result = new T[length];
		for (int i = 0; i < length; i++) {
			result[i] = a[i] * b;
		}
		return result;
	}

	template<class T>
	static T* _vector_crossproduct(T* a, T* b) {
		T* result = new T[3];
		result[0] = a[1] * b[2] - a[2] * b[1];
		result[1] = a[2] * b[0] - a[0] * b[2];
		result[2] = a[0] * b[1] - a[1] * b[0];
		return result;
	}

	template<class T>
	static T _fast_inv_sqrt(T sum) {
		T x2 = sum * 0.5f;
		T y = sum;
		long i = *(long*)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(T*)&i;
		y = y * (1.5f - (x2 * y * y));
		return y;
	}



	static void ComputeTangentFrameImpl(uint32_t vertex_count, uint32_t tri_count, uint16_t* indices, float* positions, float* UV, float* normals, float* tan, float* bit) {
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


			if (memcmp(t, zeros, 3) == 0|| memcmp(b, zeros, 3) == 0) {
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
};
namespace array_ops {
	struct FloatArray {
		float values[3];

		void normalize() {
			float length = sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);
			values[0] /= length;
			values[1] /= length;
			values[2] /= length;
		}

		// Overload the equality operator to use FloatArray as a key in unordered_map
		bool operator==(const FloatArray& other) const {
			return std::memcmp(values, other.values, 3 * sizeof(float)) == 0;
		}

		void operator=(const FloatArray& other) {
			std::memcpy(values, other.values, sizeof(values));
		}

		void operator+=(const FloatArray& other) {
			for (int i = 0; i < 3; ++i) {
				values[i] += other.values[i];
			}
		}

		void operator/=(const float& other) {
			for (int i = 0; i < 3; ++i) {
				values[i] /= other;
			}
		}
	};

	inline const std::vector<FloatArray> organizeData(const std::vector<float>& plain);

	inline const std::vector<float> flattenData(const std::vector<FloatArray>& organized);

	size_t normalizeByAttributes(const std::vector<float>& plainAttributes, std::vector<float>& plainValues);

}

class xf {
public:
	static Eigen::Matrix4f createTransformationMatrix(const Eigen::Matrix3f& R, const Eigen::Vector3f& t, float s) {
		Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

		// Fill in the upper-left 3x3 submatrix with the rotation matrix
		T_4x4.block(0, 0, 3, 3) = R;

		// Fill in the rightmost column with the translation vector and scaling
		T_4x4(0, 3) = t.x();
		T_4x4(1, 3) = t.y();
		T_4x4(2, 3) = t.z();

		// Apply scaling in the diagonal elements
		T_4x4(0, 0) *= s;
		T_4x4(1, 1) *= s;
		T_4x4(2, 2) *= s;

		return T_4x4;
	};

	static Eigen::Matrix4f createTransformationMatrix(const float R[3][3], const float t[3]) {
		Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

		// Fill in the upper-left 3x3 submatrix with the rotation matrix
		T_4x4.block(0, 0, 3, 3) <<
			R[0][0], R[0][1], R[0][2],
			R[1][0], R[1][1], R[1][2],
			R[2][0], R[2][1], R[2][2];

		// Fill in the rightmost column with the translation vector and scaling
		T_4x4(0, 3) = t[0];
		T_4x4(1, 3) = t[1];
		T_4x4(2, 3) = t[2];

		return T_4x4;
	};

	static Eigen::Matrix4f createTransformationMatrix(const float R[3][3]) {
		Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

		// Fill in the upper-left 3x3 submatrix with the rotation matrix
		T_4x4.block(0, 0, 3, 3) <<
			R[0][0], R[0][1], R[0][2],
			R[1][0], R[1][1], R[1][2],
			R[2][0], R[2][1], R[2][2];


		return T_4x4;
	};

	static Eigen::Matrix4f createTransformationMatrix(const float t[3]) {
		Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

		// Fill in the rightmost column with the translation vector and scaling
		T_4x4(0, 3) = t[0];
		T_4x4(1, 3) = t[1];
		T_4x4(2, 3) = t[2];


		return T_4x4;
	};

	static Eigen::Matrix4f createTransformationMatrix(const float s) {
		Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

		// Apply scaling in the diagonal elements
		T_4x4(0, 0) *= s;
		T_4x4(1, 1) *= s;
		T_4x4(2, 2) *= s;

		return T_4x4;
	};

	static Eigen::Vector4f fromTransform(const float t[3]) {
		Eigen::Vector4f T_4x4 = Eigen::Vector4f::Zero();

		// Fill in the rightmost column with the translation vector and scaling
		T_4x4(0) = t[0];
		T_4x4(1) = t[1];
		T_4x4(2) = t[2];
		T_4x4(3) = 1;

		return T_4x4;
	};

	static std::pair<Eigen::Vector3f, Eigen::Vector3f> toAxis(Eigen::Matrix4f& Trans, float length = 1) {
		Eigen::Vector4f start_point_homogeneous(0, 0, 0, 1);
		Eigen::Vector4f end_point_homogeneous(0, 0, length, 1);

		// Transform the start and end points
		Eigen::Vector4f transformed_start_point = Trans * start_point_homogeneous;
		Eigen::Vector4f transformed_end_point = Trans * end_point_homogeneous;

		// Convert from homogeneous coordinates to 3D Cartesian coordinates
		Eigen::Vector3f transformed_start_3d = transformed_start_point.hnormalized();
		Eigen::Vector3f transformed_end_3d = transformed_end_point.hnormalized();

		return std::make_pair(transformed_start_3d, transformed_end_3d);
	};

	static Eigen::Matrix4f toAxis(Eigen::Matrix4f& Trans, Eigen::Matrix4f& old_axis) {
		return Trans * old_axis;
	};
	
	static void decomposeTransformation(const Eigen::Matrix4f& T_4x4, Eigen::Matrix4f& R_4x4, Eigen::Matrix4f& t_4x4) {
		// Create 4x4 matrices for R_4x4 and t_4x4
		R_4x4.setIdentity();
		R_4x4.block(0, 0, 3, 3) = T_4x4.block(0, 0, 3, 3);

		t_4x4.setIdentity();
		t_4x4.block(0, 3, 3, 1) = T_4x4.block(0, 3, 3, 1);

	}

	static Eigen::Matrix4f quickInverse(const Eigen::Matrix4f& T) {
		Eigen::Matrix4f T_inv = Eigen::Matrix4f::Identity();
		T_inv.block(0,0,3,3) = T.block(0,0,3,3).transpose();
		T_inv.block(0,3,3,1) = -T_inv.block(0,0,3,3) * T.block(0,3,3,1);
		T_inv(3,3) = 1;
		return T_inv;
	}
};

// Custom hash function for FloatArray
namespace std {
	template <>
	struct hash<array_ops::FloatArray> {
		size_t operator()(const array_ops::FloatArray& arr) const {
			size_t hashValue = 0;
			for (int i = 0; i < 3; ++i) {
				hashValue ^= std::hash<float>{}(arr.values[i]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
			}
			return hashValue;
		}
	};
}