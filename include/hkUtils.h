#pragma once
#include <stdint.h>
#include <vector>
#include "Utils.h"
#include <exception>

namespace utils {
	class hk {
	public:
		struct HavokVarInfo {
			int BitCount;
			int ByteCount;
			uint8_t Prefix;
		};

		static const HavokVarInfo VarUIntTypes[8];

		static int GetLength(uint8_t prefix) {
			for (const HavokVarInfo& varIntInfo : VarUIntTypes) {
				int prefixMask = ~((1 << (varIntInfo.BitCount % 8)) - 1);
				if ((prefix & prefixMask) != varIntInfo.Prefix) continue;

				return varIntInfo.ByteCount;
			}

			throw std::exception("Invalid prefix");
		}

		static uint64_t readHavokVarUInt(const uint8_t* buf, size_t& cur_pos, bool big_endian = true) {
			uint8_t prefix = buf[cur_pos];
			int length = GetLength(prefix);
			if (length == 1) {
				cur_pos++;
				return prefix;
			}

			/*if (buf[cur_pos + 1] == 0b10100000) {
				std::cout << "Invalid prefix" << std::endl;
			}*/

			uint64_t value = 0;

			if (big_endian) {
				for (int i = 1; i < length; i++) {
					value |= buf[cur_pos + i] << (8 * (length - i - 1));
				}
			}
			else {
				for (int i = 1; i < length; i++) {
					value |= buf[cur_pos + i] << (8 * (i - 1));
				}
			}

			cur_pos += length;
			return value;
		}
	};
}