#pragma once
#include <vector>
#include <string>
#include "Common.h"
#include "hkUtils.h"

namespace utils {
	class DataAccessProfiler; 
	class IDataAccessProfiler;
	class ODataAccessProfiler;

	class ProfilerGlobalOwner {
	public:
		struct Record {
			uint8_t* data;
			size_t size;
			DataAccessProfiler* profiler;
		};

		static ProfilerGlobalOwner& GetInstance() {
			static ProfilerGlobalOwner instance;
			return instance;
		}

		std::vector<Record> profilers;

		void Flush();

		void AddProfiler(DataAccessProfiler* profiler);

		void ReleaseProfiler(DataAccessProfiler* profiler);

		void ReleaseAll();

		void for_each(std::function<void(DataAccessProfiler*)> func);

	private:
		ProfilerGlobalOwner() {};
	};

	class DataAccessor {
	public:
		enum class AccessOptions: uint8_t {
			None = 0,
			Profiler = 1 << 0,
			NoOverread = 1 << 1,
			NoOverwrite = 1 << 2,
		};

		DataAccessor() {};
		~DataAccessor();

		static DataAccessor Alloc(size_t size, uint8_t default_value = 0, uint8_t options = AccessOptions::Profiler | AccessOptions::NoOverread | AccessOptions::NoOverwrite);

		static DataAccessor Create(const uint8_t* data, size_t size, bool is_owner = false, uint8_t options = AccessOptions::Profiler | AccessOptions::NoOverread | AccessOptions::NoOverwrite);

		//DataAccessor(const uint8_t* data, size_t size, uint8_t options = AccessOptions::Profiler | AccessOptions::NoOverread | AccessOptions::NoOverwrite);

		DataAccessor(const DataAccessor& other);
		DataAccessor& operator=(const DataAccessor& other);

		uint8_t* start = nullptr;
		uint8_t* data = nullptr;
		size_t size = 0;
		DataAccessProfiler* read_profiler = nullptr;
		DataAccessProfiler* write_profiler = nullptr;
		AccessOptions _options = AccessOptions::None;

		DataAccessor operator+(size_t offset);

		uint64_t operator-(const DataAccessor& other);

		template<_base_type_t T>
		T read(size_t& offset, bool big_endian = false);

		template<_base_type_t T>
		bool write(size_t& offset, T value, bool big_endian = false);

		void mark_read(size_t offset);

		void mark_write(size_t offset);

		uint8_t operator[](size_t offset);

		DataAccessor operator +=(size_t offset);

		bool is_valid() const;

		DataAccessor Weld(const utils::DataAccessor& other);

		static DataAccessor WeldAll(const std::vector<utils::DataAccessor>& accessors);

		//uint64_t get_offset() const;

		DataAccessor deep_copy(size_t size = -1) const;

		DataAccessor make_reference();

		void Destroy();
	protected:
		bool _is_owner = false;
	};

	class DataAccessProfiler {
	public:
		DataAccessProfiler(uint8_t* offset, size_t size, DataAccessor::AccessOptions options);

		~DataAccessProfiler() {
			delete[] accessed;
		}

		uint8_t* offset;
		size_t size;
		uint8_t* accessed;
		size_t accessed_record_size;
		DataAccessor::AccessOptions _options;

		std::vector<uint64_t> markers;

		void Flush();

		virtual std::string GetRTTIName() = 0;

		virtual bool Access(size_t offset, size_t byte_size) = 0;

		inline bool has_accessed(size_t offset);

		void dump(std::ostream& out);

		void mark(size_t offset);
	};

	class IDataAccessProfiler :public DataAccessProfiler {
	public:
		IDataAccessProfiler(uint8_t* offset, size_t size, DataAccessor::AccessOptions options) : DataAccessProfiler(offset, size, options) {
		}

		std::string GetRTTIName() override {
			return "IDataAccessProfiler";
		}

		bool Access(size_t offset, size_t byte_size) override;
	};

	class ODataAccessProfiler :public DataAccessProfiler {
	public:
		ODataAccessProfiler(uint8_t* offset, size_t size, DataAccessor::AccessOptions options) : DataAccessProfiler(offset, size, options) {
		}

		std::string GetRTTIName() override {
			return "ODataAccessProfiler";
		}

		bool Access(size_t offset, size_t byte_size) override;
	};

	template<_base_type_t T>
	T readFromAccessor(DataAccessor& accessor, size_t& offset, bool big_endian = false) {
		return accessor.read<T>(offset, big_endian);
	}

	template<_base_type_t T>
	bool writeToAccessor(DataAccessor& accessor, size_t& offset, T value, bool big_endian = false) {
		return accessor.write<T>(offset, value, big_endian);
	}

	std::string readStringFromAccessor(DataAccessor& accessor, size_t& offset, size_t length);

	bool writeStringToAccessor(DataAccessor& accessor, size_t& offset, const std::string& value);

	uint64_t readHavokVarUIntFromAccessor(DataAccessor& accessor, size_t& offset);

	bool writeHavokVarUIntToAccessor(DataAccessor& accessor, size_t& offset, uint64_t value);

	float readHalfAsFullFromAccessor(DataAccessor& accessor, size_t& offset, bool big_endian = false);

	bool writeHalfAsFullToAccessor(DataAccessor& accessor, size_t& offset, float value, bool big_endian = false);
	
	template<_base_type_t T>
	inline T DataAccessor::read(size_t& offset, bool big_endian)
	{
		if (read_profiler) {
			auto success = read_profiler->Access(this->data + offset - read_profiler->offset, sizeof(T));
			if (!success) {
				throw std::exception("Access denied");
			}
		}

		if (big_endian) {
			T result = switchEndian(*(T*)(data + offset));
			offset += sizeof(T);
			return result;
		}
		else {
			T result = *(T*)(data + offset);
			offset += sizeof(T);
			return result;
		}
	}

	template<_base_type_t T>
	inline bool DataAccessor::write(size_t& offset, T value, bool big_endian)
	{
		if (write_profiler) {
			auto success = write_profiler->Access(this->data + offset - write_profiler->offset, sizeof(T));
			if (!success) {
				return false;
			}
		}

		if (big_endian) {
			*(T*)(data + offset) = switchEndian(value);
			offset += sizeof(T);
		}
		else {
			*(T*)(data + offset) = value;
			offset += sizeof(T);
		}
		return true;
	}

}