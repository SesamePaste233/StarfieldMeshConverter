#include "DataAccessor.h"

namespace utils{

	bool IDataAccessProfiler::Access(size_t offset, size_t byte_size)
	{
		if (offset + byte_size > size) {
#ifdef _DEBUG
			throw std::exception("Access out of range");
#endif
			return false;
		}

		for (size_t i = offset; i < offset + byte_size; i++) {
			if (this->_options & DataAccessor::AccessOptions::NoOverread && this->accessed[i / 8] & (1 << (i % 8))) {
				std::cout << "Overread at " << std::hex << i << std::endl;
				return false;
			}
			this->accessed[i / 8] |= 1 << (i % 8);
		}
		return true;
	}

	bool ODataAccessProfiler::Access(size_t offset, size_t byte_size)
	{
		if (offset + byte_size > size) {
#ifdef _DEBUG
			throw std::exception("Access out of range");
#endif
			return false;
		}

		for (size_t i = offset; i < offset + byte_size; i++) {
			if (this->_options & DataAccessor::AccessOptions::NoOverwrite && this->accessed[i / 8] & (1 << (i % 8))) {
				std::cout << "Overwrite at " << std::hex << i << std::endl;
				return false;
			}
			this->accessed[i / 8] |= 1 << (i % 8);
		}
		return true;
	}

	DataAccessProfiler::DataAccessProfiler(uint8_t* offset, size_t size, DataAccessor::AccessOptions options) : offset(offset), size(size), _options(options) {
		accessed_record_size = size / 8 + 1;
		accessed = new uint8_t[accessed_record_size];
		std::memset(accessed, 0, accessed_record_size);

		ProfilerGlobalOwner::GetInstance().AddProfiler(this);
	}

	void DataAccessProfiler::Flush() {
		std::memset(accessed, 0, accessed_record_size);
	}

	inline bool DataAccessProfiler::has_accessed(size_t offset) {
		return accessed[offset / 8] & (1 << (offset % 8));
	}

	void DataAccessProfiler::dump(std::ostream& out) {
		uint8_t* result = new uint8_t[size];
		for (size_t i = 0; i < size; ++i) {
			if (has_accessed(i)) {
				result[i] = 0xFF;
			}
			else {
				result[i] = 0x00;
			}
		}
		utils::writeStream(out, result, size);
	}

	DataAccessor::DataAccessor(const uint8_t* data, size_t size, uint8_t options) : data(const_cast<uint8_t*>(data)), size(size), _options((AccessOptions)options) {
#ifdef _DEBUG
		
#else
		_options = AccessOptions::None;
#endif
		if (_options & AccessOptions::Profiler) {
			read_profiler = new IDataAccessProfiler(this->data, this->size, this->_options);
			write_profiler = new ODataAccessProfiler(this->data, this->size, this->_options);
		}
	}

	DataAccessor::DataAccessor(const DataAccessor& other) {
		data = other.data;
		size = other.size;
		_options = other._options;
		read_profiler = other.read_profiler;
		write_profiler = other.write_profiler;
	}
	DataAccessor DataAccessor::operator+(size_t offset) {
		return DataAccessor(data + offset, size - offset, _options, read_profiler, write_profiler);
	}

	uint64_t DataAccessor::operator-(const DataAccessor& other) {
		return data - other.data;
	}

	uint8_t DataAccessor::operator[](size_t offset) {
		return read<uint8_t>(offset);
	}


	DataAccessor DataAccessor::operator+=(size_t offset) {
		this->data += offset;
		this->size -= offset;
		return *this;
	}

	bool DataAccessor::is_valid() const {
		return data != nullptr;
	}

	DataAccessor DataAccessor::deep_copy(size_t size) const
	{
		if (size == -1) {
			size = this->size;
		}

		if (!this->is_valid()) {
			return DataAccessor();
		}
		auto new_buffer = new uint8_t[size];
		std::memcpy(const_cast<uint8_t*>(new_buffer), this->data, size);
		return DataAccessor(new_buffer, size, uint8_t(_options));
	}

	std::string readStringFromAccessor(DataAccessor& accessor, size_t& offset, size_t length) {
		std::string result;
		result.resize(length);
		for (size_t i = 0; i < length; i++) {
			result[i] = accessor.read<uint8_t>(offset, false);
		}
		return result;
	}

	bool writeStringToAccessor(DataAccessor& accessor, size_t& offset, const std::string& value) {
		for (size_t i = 0; i < value.size(); i++) {
			accessor.write<uint8_t>(offset, value[i], false);
		}
		return true;
	}

	uint64_t readHavokVarUIntFromAccessor(DataAccessor& accessor, size_t& offset, bool big_endian) {
		uint8_t prefix = accessor.read<uint8_t>(offset, big_endian);
		int length = utils::hk::GetLength(prefix);
		if (length == 1) {
			return prefix;
		}

		uint64_t value = 0;

		if (big_endian) {
			for (int i = 1; i < length; i++) {
				value |= accessor.read<uint8_t>(offset, big_endian) << (8 * (length - i - 1));
			}
		}
		else {
			for (int i = 1; i < length; i++) {
				value |= accessor.read<uint8_t>(offset, big_endian) << (8 * (i - 1));
			}
		}

		return value;
	}

	bool writeHavokVarUIntToAccessor(DataAccessor& accessor, size_t& offset, uint64_t value, bool big_endian)
	{
		if (value > 0x80) {
			uint8_t prefix = 0;
			int length = 0;
			for (const utils::hk::HavokVarInfo& varIntInfo : utils::hk::VarUIntTypes) {
				if (value < (1 << varIntInfo.BitCount)) {
					prefix = varIntInfo.Prefix;
					length = varIntInfo.ByteCount;
					break;
				}
			}
			if (length == 0) {
				return false;
			}
			accessor.write<uint8_t>(offset, prefix, big_endian);
			if (big_endian) {
				for (int i = 1; i < length; i++) {
					accessor.write<uint8_t>(offset, value >> (8 * (length - i - 1)), big_endian);
				}
			}
			else {
				for (int i = 1; i < length; i++) {
					accessor.write<uint8_t>(offset, value >> (8 * (i - 1)), big_endian);
				}
			}
		}
		else {
			accessor.write<uint8_t>(offset, value, big_endian);
		}
	}

	float readHalfAsFullFromAccessor(DataAccessor& accessor, size_t& offset, bool big_endian) {
		uint16_t half = accessor.read<uint16_t>(offset, big_endian);
		return halfToFloat(half);
	}

	bool writeHalfAsFullToAccessor(DataAccessor& accessor, size_t& offset, float value, bool big_endian)
	{
		uint16_t half = floatToHalf(value);
		accessor.write<uint16_t>(offset, half, big_endian);
		return true;
	}
	void ProfilerGlobalOwner::Flush()
	{
		for (auto& record : profilers) {
			record.profiler->Flush();
		}
	}
	void ProfilerGlobalOwner::AddProfiler(DataAccessProfiler* profiler)
	{
		profilers.push_back({ profiler->offset, profiler->size, profiler });
	}
	void ProfilerGlobalOwner::ReleaseProfiler(DataAccessProfiler* profiler)
	{
		auto it = std::find_if(profilers.begin(), profilers.end(), [profiler](const Record& record) {
			return record.profiler == profiler;
			});
		if (it != profilers.end()) {
			profilers.erase(it);
			delete profiler;
		}
	}
	void ProfilerGlobalOwner::ReleaseAll()
	{
		for (auto& record : profilers) {
			delete record.profiler;
		}
		profilers.clear();
	}

	void ProfilerGlobalOwner::for_each(std::function<void(DataAccessProfiler*)> func)
	{
		for (auto& record : profilers) {
			func(record.profiler);
		}
	}
}
