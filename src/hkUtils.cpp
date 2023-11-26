#include "hkUtils.h"

using namespace utils;

const utils::hk::hkVarUIntInfo utils::hk::hkVarUInt_info[8] = {
	{0b10000000, 7, 1, 0},
	{0b11000000, 14, 2, 0b10000000},
	{0b11100000, 21, 3, 0b11000000},
	{0b11111000, 27, 4, 0b11100000},
	{0b11111000, 35, 5, 0b11101000},
	{0b11111111, 40, 6, 0b11111000},
	{0b11111000, 59, 8, 0b11110000},
	{0b11111111, 64, 9, 0b11111001}
};

uint64_t utils::SerializePool::QueueSerialization(SerializableBase* obj, bool is_owner)
{
	if (!obj) {
		return -1;
	}

	if (obj->Serialized()) {
		return obj->serialized_index;
	}
	pool.push({ obj,is_owner });
	return _index_begin + pool.size() - 1;
}

uint64_t utils::SerializePool::Resolve(DataAccessor accessor, size_t& total_size)
{
	uint64_t i = 0;
	uint32_t offset = 0;
	while (!pool.empty()) {
		auto obj = pool.front().first;
		auto is_owner = pool.front().second;
		offset = obj->Serialize(accessor, *this);
		total_size += offset;
		accessor += offset;
		obj->serialized_index = _index_begin + i;
		if (is_owner) serialized_objects.push_back(obj);
		pool.pop();
		_index_begin++;
		i++;
	}
	return i;
}
