#include "hkUtils.h"

using namespace utils;

const utils::hk::HavokVarInfo utils::hk::VarUIntTypes[8] = {
    {7, 1, 0},
    {14, 2, 0b10000000},
    {21, 3, 0b11000000},
    {27, 4, 0b11100000},
    {35, 5, 0b11101000},
    {40, 6, 0b11111000},
    {59, 8, 0b11110000},
    {64, 9, 0b11111001}
};

uint64_t utils::SerializePool::QueueSerialization(SerializableBase* obj)
{
    if (!obj) {
		return -1;
	}

    if (obj->Serialized()) {
        return obj->serialized_index;
    }
    pool.push(obj);
    return _index_begin + pool.size() - 1;
}
