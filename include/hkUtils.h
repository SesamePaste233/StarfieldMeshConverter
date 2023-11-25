#pragma once
#include <stdint.h>
#include <vector>
#include "Utils.h"
#include "DataAccessor.h"
#include <exception>
#include <queue>

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

	class SerializableBase;
	class DataAccessor;

	class SerializePool {
	public:
		SerializePool(uint64_t index_begin): _index_begin(index_begin) {};

		uint64_t _index_begin = 0;

		std::queue<SerializableBase*> pool;

		uint64_t QueueSerialization(SerializableBase* obj);
	};

	class SerializableBase {
	public:
		uint64_t serialized_index = -1;

		virtual uint64_t Serialize(utils::DataAccessor data, SerializePool& serializer) = 0;

		bool Serialized() {
			return serialized_index != -1;
		}
	};
}