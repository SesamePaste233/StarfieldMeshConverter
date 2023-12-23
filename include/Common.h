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
#include <set>

// Necessary for havok physics
#include <Eigen/Dense>

#include "Utils.h"
#include "xfUtils.h"

template <typename T>
concept IsFlagEnum = std::is_enum_v<T> && (std::is_same_v<std::underlying_type_t<T>, uint8_t> || std::is_same_v<std::underlying_type_t<T>, uint16_t> || std::is_same_v<std::underlying_type_t<T>, uint32_t> || std::is_same_v<std::underlying_type_t<T>, uint64_t>);

template <IsFlagEnum T, typename _under_lying_t = std::underlying_type_t<T>>
_under_lying_t to_underlying(T t) {
	return static_cast<_under_lying_t>(t);
}


template <IsFlagEnum T>
uint64_t operator&(T lhs, T rhs) {
	using U = std::underlying_type_t<T>;
	return static_cast<uint64_t>(static_cast<U>(lhs) & static_cast<U>(rhs));
};
template <IsFlagEnum T, typename U = std::underlying_type_t<T>>
uint64_t operator&(U lhs, T rhs) {
	return static_cast<uint64_t>(static_cast<U>(lhs) & static_cast<U>(rhs));
};
template <IsFlagEnum T, typename U = std::underlying_type_t<T>>
uint64_t operator&(T lhs, U rhs) {
	return static_cast<uint64_t>(static_cast<U>(lhs) & static_cast<U>(rhs));
};

template <IsFlagEnum T>
uint64_t operator|(T lhs, T rhs) {
	using U = std::underlying_type_t<T>;
	return static_cast<uint64_t>(static_cast<U>(lhs) | static_cast<U>(rhs));
};
template <IsFlagEnum T, typename U = std::underlying_type_t<T>>
uint64_t operator|(U lhs, T rhs) {
	return static_cast<uint64_t>(static_cast<U>(lhs) | static_cast<U>(rhs));
};
template <IsFlagEnum T, typename U = std::underlying_type_t<T>>
uint64_t operator|(T lhs, U rhs) {
	return static_cast<uint64_t>(static_cast<U>(lhs) | static_cast<U>(rhs));
};

template <IsFlagEnum T>
T operator|=(T& lhs, T rhs) {
	using U = std::underlying_type_t<T>;
	return lhs = static_cast<T>(static_cast<U>(lhs) | static_cast<U>(rhs));
};

template <IsFlagEnum T, typename U = std::underlying_type_t<T>>
T operator|=(T& lhs, U rhs) {
	return lhs = static_cast<T>(static_cast<U>(lhs) | static_cast<U>(rhs));
};


template <IsFlagEnum T>
uint8_t operator~(T rhs) {
	using U = std::underlying_type_t<T>;
	return ~static_cast<U>(rhs);
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