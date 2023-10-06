#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <algorithm>
#include <unordered_map>

class Util {
public:
	static std::vector<float> decodeUDEC3_2(uint32_t n) {
		float x, y, z, w;
		x = ((n & 1023) / 511.5) - 1.0;

		y = (((n >> 10) & 1023) / 511.5) - 1.0;

		z = (((n >> 20) & 1023) / 511.5) - 1.0;

		w = (n >> 30) & 3;

		return { x,y,z };
	}

	static std::uint32_t encodeUDEC3_2(const std::vector<float>& values, bool w) {

		std::uint32_t n = 0;
		n |= static_cast<std::uint32_t>((values[0] + 1.0f) * 511.5f) & 1023;
		n |= (static_cast<std::uint32_t>((values[1] + 1.0f) * 511.5f) & 1023) << 10;
		n |= (static_cast<std::uint32_t>((values[2] + 1.0f) * 511.5f) & 1023) << 20;

		// Add the encoded 'w' value (default is 1).
		if(w) n |= 1 << 30;

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
	static void writeAsHex(std::ofstream& file, T& value) {
		file.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	static std::vector<float> readHalfAsFull(std::ifstream& file, int counts = 1) {
		std::vector<float> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint16_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
			result.push_back(halfToFloat(value));
		}
		return result;
	}

	// Equivalent of readDouble in C++
	static std::vector<double> readDouble(std::ifstream& file, int counts = 1) {
		std::vector<double> result;
		result.reserve(8 * counts);
		for (int i = 0; i < 8 * counts; ++i) {
			double value;
			file.read(reinterpret_cast<char*>(&value), sizeof(double));
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

	static int16_t double_to_snorm(double value, double scale) {
		// Normalize the value to the range [-1, 1]
		value /= scale;

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
			return static_cast<int16_t>(value * 32767.0);
		}
	}

	// Equivalent of readUInt32 in C++
	static std::vector<uint32_t> readUInt32(std::ifstream& file, int counts = 1) {
		std::vector<uint32_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint32_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of readFloat in C++
	static std::vector<float> readFloat(std::ifstream& file, int counts = 1) {
		std::vector<float> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			float value;
			file.read(reinterpret_cast<char*>(&value), sizeof(float));
			result.push_back(value);
		}
		return result;
	}

	// Equivalent of readUInt8AsInt in C++
	static std::vector<uint8_t> readUInt8(std::ifstream& file, int counts = 1) {
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
	static std::vector<uint16_t> readUInt16(std::ifstream& file, int counts = 1) {
		std::vector<uint16_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			uint16_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
			result.push_back(value);
		}
		return result;
	}

	static std::vector<int16_t> readInt16(std::ifstream& file, int counts = 1) {
		std::vector<int16_t> result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			int16_t value;
			file.read(reinterpret_cast<char*>(&value), sizeof(int16_t));
			result.push_back(value);
		}
		return result;
	}

	static std::string readString(std::ifstream& file, int counts = 1) {
		std::string result;
		result.reserve(counts);
		for (int i = 0; i < counts; ++i) {
			char value;
			file.read(reinterpret_cast<char*>(&value), sizeof(char));
			result.push_back(value);
		}
		return result;
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
			while (_n) {
				if (_n & 1) {
					positions.push_back(count);
				}
				count++;
				_n >>= 1;
			}
		}
		return positions;
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
			return std::memcmp(values, other.values, sizeof(values)) == 0;
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