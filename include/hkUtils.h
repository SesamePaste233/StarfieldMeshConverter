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
		struct hkVarUIntInfo {
			uint8_t pref_mask;
			int bit_count;
			int byte_count;
			uint8_t hk_prefix;
		};

		static const hkVarUIntInfo hkVarUInt_info[8];

		static hkVarUIntInfo GetHavokVarUIntInfo(uint8_t prefix) {
			for (const hkVarUIntInfo& varIntInfo : hkVarUInt_info) {
				if ((prefix & varIntInfo.pref_mask) == varIntInfo.hk_prefix) {
					return varIntInfo;
				}
			}

			throw std::exception("Invalid prefix");
		}

		static hkVarUIntInfo GetHavokVarUIntAllocInfo(size_t bit_count) {
			for (const hkVarUIntInfo& varIntInfo : hkVarUInt_info) {
				if (varIntInfo.bit_count >= bit_count) {
					return varIntInfo;
				}
			}

			throw std::exception("Invalid bit count");
		}

		static uint64_t readHavokVarUInt(const uint8_t* buf, size_t& cur_pos, bool big_endian = true) {
			uint8_t prefix = buf[cur_pos];
			hkVarUIntInfo info = GetHavokVarUIntInfo(prefix);
			auto length = info.byte_count;
			if (info.byte_count == 1) {
				cur_pos++;
				return prefix;
			}
			uint64_t value = prefix & ~info.pref_mask;

			if (big_endian) {
				for (int i = 1; i < length; i++) {
					value |= (uint64_t)buf[cur_pos + i] << (8 * (length - i - 1));
				}
			}
			else {
				for (int i = 1; i < length; i++) {
					value |= (uint64_t)buf[cur_pos + i] << (8 * (i - 1));
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

		std::queue<std::pair<SerializableBase*, bool>> pool;
		std::vector<SerializableBase*> serialized_objects;

		// Returns the index of the object in the pool
		uint64_t QueueSerialization(SerializableBase* obj, bool is_owner);

		// Returns the number of objects serialized
		uint64_t Resolve(DataAccessor accessor, size_t& total_size);
	};

	class SerializableBase {
	public:
		virtual ~SerializableBase() = default;

		uint64_t serialized_index = -1;

		virtual uint64_t Serialize(utils::DataAccessor data, SerializePool& serializer) = 0;

		bool Serialized() {
			return serialized_index != -1;
		}
	};

}