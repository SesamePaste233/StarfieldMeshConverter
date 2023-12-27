#include "DataAccessor.h"

namespace utils{

	bool IDataAccessProfiler::Access(size_t offset, size_t byte_size)
	{
		if (offset + byte_size > size) {
			throw std::exception("Access out of range");
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
			throw std::exception("Access out of range");
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
		std::sort(markers.begin(), markers.end());

		auto iter = markers.begin();
		uint8_t* result = new uint8_t[size];
		auto sig = 0xFF;
		for (size_t i = 0; i < size; ++i) {
			while (iter != markers.end() && *iter == i) {
				sig--;
				if (sig == 0) {
					sig = 0xFF;
				}
				iter++;
			}
			if (has_accessed(i)) {
				result[i] = sig;
			}
			else {
				result[i] = 0x00;
			}
		}
		utils::writeStream(out, result, size);
	}

	void DataAccessProfiler::mark(size_t offset)
	{
		markers.push_back(offset);
	}

	DataAccessor::~DataAccessor()
	{
		Destroy();
	}

	DataAccessor DataAccessor::Alloc(size_t size, uint8_t default_value, uint8_t options)
	{
		DataAccessor result;
		result.data = new uint8_t[size];
		result.start = result.data;
		std::memset(result.data, default_value, size);
		result.size = size;
		result._options = (AccessOptions)options;
		if (result._options & AccessOptions::Profiler) {
			result.read_profiler = new IDataAccessProfiler(result.data, result.size, result._options);
			result.write_profiler = new ODataAccessProfiler(result.data, result.size, result._options);
		}
		result._is_owner = true;

#ifdef _DEBUG
		std::cout << "DataAccessor Allocated " << std::to_string(size) << " bytes at " << std::hex << (uintptr_t)result.start << std::endl;
#endif

		return result;
	}

	DataAccessor DataAccessor::Create(const uint8_t* data, size_t size, bool is_owner, uint8_t options)
	{
		DataAccessor result;
		result.data = const_cast<uint8_t*>(data);
		result.start = result.data;
		result.size = size;
		result._options = (AccessOptions)options;
		if (result._options & AccessOptions::Profiler) {
			result.read_profiler = new IDataAccessProfiler(result.data, result.size, result._options);
			result.write_profiler = new ODataAccessProfiler(result.data, result.size, result._options);
		}
		result._is_owner = is_owner;

#ifdef _DEBUG
		if (is_owner) {
			std::cout << "DataAccessor Owned " << std::to_string(size) << " bytes at " << std::hex << (uintptr_t)result.start << std::endl;
		}
#endif
		return result;
	}

	DataAccessor::DataAccessor(const DataAccessor& other) {
		start = other.start;
		data = other.data;
		size = other.size;
		_options = other._options;
		read_profiler = other.read_profiler;
		write_profiler = other.write_profiler;
		if (other._is_owner) {
			_is_owner = true;
			const_cast<DataAccessor*>(&other)->_is_owner = false;
		}
	}

	DataAccessor& DataAccessor::operator=(const DataAccessor& other)
	{
		if (this != &other){
			start = other.start;
			data = other.data;
			size = other.size;
			_options = other._options;
			read_profiler = other.read_profiler;
			write_profiler = other.write_profiler;
			if (other._is_owner) {
				_is_owner = true;
				const_cast<DataAccessor*>(&other)->_is_owner = false;
			}
		}

		return *this;
	}

	DataAccessor DataAccessor::operator+(size_t offset) {
		DataAccessor result = *this;
		result.data += offset;
		result.size -= offset;
		return result;
	}

	uint64_t DataAccessor::operator-(const DataAccessor& other) {
		return data - other.data;
	}

	void DataAccessor::mark_read(size_t offset)
	{
		if (read_profiler) {
			read_profiler->mark(this->data + offset - read_profiler->offset);
		}
	}

	void DataAccessor::mark_write(size_t offset)
	{
		if (write_profiler) {
			write_profiler->mark(this->data + offset - write_profiler->offset);
		}
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

	DataAccessor DataAccessor::Weld(const utils::DataAccessor& other)
	{
		if (!other.is_valid()) {
			return *this;
		}
		if (!this->_is_owner) {
			throw std::exception("Cannot weld to non-owner");
		}
		// Allocate new buffer
		auto new_buffer = new uint8_t[this->size + other.size];
		std::memcpy(new_buffer, this->data, this->size);
		std::memcpy(new_buffer + this->size, other.data, other.size);
		auto rtn = DataAccessor::Create(new_buffer, this->size + other.size, true, uint8_t(_options));
		return rtn;
	}

	DataAccessor DataAccessor::WeldAll(const std::vector<utils::DataAccessor>& accessors)
	{
		if (accessors.size() == 0) {
			return DataAccessor();
		}
		if (!accessors[0].is_valid()) {
			return DataAccessor();
		}
		if (!accessors[0]._is_owner) {
			throw std::exception("Cannot weld to non-owner");
		}
		// Allocate new buffer
		size_t total_size = 0;
		for (auto& accessor : accessors) {
			total_size += accessor.size;
		}
		auto new_buffer = new uint8_t[total_size];
		size_t offset = 0;
		for (auto& accessor : accessors) {
			std::memcpy(new_buffer + offset, accessor.data, accessor.size);
			offset += accessor.size;
		}
		auto rtn = DataAccessor::Create(new_buffer, total_size, true, uint8_t(accessors[0]._options));
		return rtn;
	}

	DataAccessor DataAccessor::AppendAll(const std::vector<utils::DataAccessor>& accessors)
	{
		if (accessors.size() == 0) {
			return DataAccessor();
		}
		if (!accessors[0].is_valid()) {
			return DataAccessor();
		}
		if (!accessors[0]._is_owner) {
			throw std::exception("Cannot weld to non-owner");
		}
		if (!this->_is_owner) {
			throw std::exception("Cannot weld to non-owner");
		}
		// Allocate new buffer
		size_t total_size = this->size;
		for (auto& accessor : accessors) {
			total_size += accessor.size;
		}
		auto new_buffer = new uint8_t[total_size];
		std::memcpy(new_buffer, this->data, this->size);
		size_t offset = this->size;
		for (auto& accessor : accessors) {
			std::memcpy(new_buffer + offset, accessor.data, accessor.size);
			offset += accessor.size;
		}
		auto rtn = DataAccessor::Create(new_buffer, total_size, true, uint8_t(accessors[0]._options));
		return rtn;
	}

	/*uint64_t DataAccessor::get_offset() const
	{
		return data - start;
	}*/

	DataAccessor DataAccessor::deep_copy(size_t size) const
	{
		if (size == -1) {
			size = this->size;
		}

		if (!this->is_valid()) {
			throw std::exception("Cannot deep copy invalid accessor");
		}
		auto new_buffer = new uint8_t[size];
		std::memcpy(const_cast<uint8_t*>(new_buffer), this->data, size);
		auto rtn = DataAccessor::Create(new_buffer, size, true, uint8_t(_options));
		return rtn;
	}

	DataAccessor DataAccessor::make_reference()
	{
		if (!this->is_valid()) {
			throw std::exception("Cannot make reference to invalid accessor");
		}
		auto rtn = DataAccessor();
		rtn.start = this->start;
		rtn.data = this->data;
		rtn.size = this->size;
		rtn._options = this->_options;
		rtn.read_profiler = this->read_profiler;
		rtn.write_profiler = this->write_profiler;
		rtn._is_owner = false;
		return rtn;
	}

	void DataAccessor::Destroy()
	{
		if (_is_owner) {
			if (_options & AccessOptions::Profiler) {
				ProfilerGlobalOwner::GetInstance().ReleaseProfiler(read_profiler);
				ProfilerGlobalOwner::GetInstance().ReleaseProfiler(write_profiler);
			}
			if (start) {
#ifdef _DEBUG
				std::cout << "DataAccessor Freed " << std::to_string(data - start + size) << " bytes at " << std::hex << (uintptr_t)start << std::endl;
#endif
				delete[] start;
			}
		}
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

	uint64_t readHavokVarUIntFromAccessor(DataAccessor& accessor, size_t& offset) {
		uint8_t prefix = accessor[offset];

		auto info = utils::hk::GetHavokVarUIntInfo(prefix);
		uint64_t value = prefix;
		value &= ~info.pref_mask;
		value <<= 8 * (info.byte_count - 1);
		for (int i = 1; i < info.byte_count; i++) {
			auto v = (uint64_t)accessor[offset + i];
			value |= v << (8 * (info.byte_count - i - 1));
		}
		offset += info.byte_count;

		return value;
	}

	bool writeHavokVarUIntToAccessor(DataAccessor& accessor, size_t& offset, uint64_t value)
	{
		// Get how many bits we need to store
		int bit_count = 0;
		for (int i = 63; i >= 0; i--) {
			if (value & ((uint64_t)1 << i)) {
				bit_count = i + 1;
				break;
			}
		}

		auto info = utils::hk::GetHavokVarUIntAllocInfo(bit_count);

		auto prefix = value >> 8 * (info.byte_count - 1);
		prefix |= info.hk_prefix;

		auto suc = accessor.write<uint8_t>(offset, prefix, false);
		if (!suc) {
			return false;
		}

		for (int i = 1; i < info.byte_count; i++) {
			auto v = (uint8_t)(value >> (8 * (info.byte_count - i - 1)));
			auto suc = accessor.write<uint8_t>(offset, v, false);
			if (!suc) {
				return false;
			}
		}

		return true;
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
#ifdef _DEBUG
		std::cout << "Registered profiler: " << (uintptr_t)profiler << std::endl;
#endif
		profilers.push_back({ profiler->offset, profiler->size, profiler });
	}
	void ProfilerGlobalOwner::ReleaseProfiler(DataAccessProfiler* profiler)
	{
#ifdef _DEBUG
		std::cout << "Unregistered profiler: " << (uintptr_t)profiler << std::endl;
#endif
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
