#pragma once
#include "Common.h"
#include "hkReflection.h"
#include "hkPhysics.h"

namespace hkreflex {
	class hkClassBase;
	class hkIndexedDataBlock;
}

namespace hkphysics {
	class hkReflDataSerializeContext;

	enum class ChunkType {
		Unknown = -1,
		TAG0, // Major data chunk					IO
			SDKV, // SDK version					IO, Has data
			DATA, // Data							IO, Has data
			TYPE, // Types							IO
				TPTR, // Type pointer				IO, 8 * num_types, all 0
				TST1, // Type names					IO, Has data
				TNA1, // Type And Template Args		IO, Has data
				FST1, // Field names				IO, Has data
				TBDY, // Type body					IO, Has data
				THSH, // Type hash					IO, Has data
				TPAD, // Type padding				IO, 4 bytes all 0
			INDX, // Index							IO
				ITEM, // Item						IO, Has data
				PTCH, // Patch						IO, Has data
	};

	std::string_view GetChunkTypeName(ChunkType type);

	ChunkType ChunkTypeFromName(const std::string name);

	class hkDataChunkBase {
	public:
		hkDataChunkBase(hkReflDataSerializeContext* owner): ref_data(owner) {
		}
		virtual ~hkDataChunkBase() {
		}
		hkReflDataSerializeContext* ref_data = nullptr;
		uint8_t chunk_decorator = -1;
		uint32_t data_size = 0;
		char type_name[4] = { 0 };

		std::vector<hkDataChunkBase*> children;

		virtual ChunkType GetType() = 0;
		virtual bool Decode() = 0;

		void Traverse(std::function<void(hkDataChunkBase*)> pre_order_function = [](hkDataChunkBase*) {}, std::function<void(hkDataChunkBase*)> post_order_function = [](hkDataChunkBase*) {}) {
			pre_order_function(this);
			for (auto child : this->children) {
				child->Traverse(pre_order_function, post_order_function);
			}
			post_order_function(this);
		}
		
		void SetName(const std::string& name) {
			std::memcpy(this->type_name, name.c_str(), 4);
		}

		static const uint8_t _leaf_decorator = 0x40;

		utils::DataAccessor GetBuffer() {
			return _accessor.make_reference();
		}

		uint32_t GetBufferSize() {
			return data_size;
		}

		uint32_t GetActualDataSize() {
			return data_size - 8;
		}

		void SetBuffer(utils::DataAccessor accessor) {
			this->_accessor = accessor;
		}

		void OwnBuffer() {
			if (!_accessor.is_valid()) {
				return;
			}
			_accessor = _accessor.deep_copy(GetBufferSize());
			_own_buffer = true;
		}

		virtual uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) {
			if (use_cached && _own_buffer) {
				out = _accessor + 8;
				return _accessor.size - 8;
			}
			return false;
		}

	protected:
		bool _own_buffer = false;
		utils::DataAccessor _accessor;
	};

	class hkDataChunkTAG0 :public hkDataChunkBase {
	public:
		hkDataChunkTAG0(hkReflDataSerializeContext* owner) : hkDataChunkBase(owner) {
			chunk_decorator = 0x00;
			type_name[0] = 'T';
			type_name[1] = 'A';
			type_name[2] = 'G';
			type_name[3] = '0';
		}
		~hkDataChunkTAG0() {
		}

		ChunkType GetType() override{
			return ChunkType::TAG0;
		}

		bool Decode() override{
			return true;
		}

		bool DistributeAndDecode(uint32_t indent = 0);

		uint64_t DistributeAndSerialize(utils::DataAccessor& out, bool use_cached = false);

	};

	class hkDataChunkSDKV : public hkDataChunkTAG0 {
	public:
		hkDataChunkSDKV(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'S';
			type_name[1] = 'D';
			type_name[2] = 'K';
			type_name[3] = 'V';
		}
		~hkDataChunkSDKV() {
		}

		ChunkType GetType() override {
			return ChunkType::SDKV;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkDATA : public hkDataChunkTAG0 {
	public:
		hkDataChunkDATA(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'D';
			type_name[1] = 'A';
			type_name[2] = 'T';
			type_name[3] = 'A';
		}
		~hkDataChunkDATA() {
		}

		ChunkType GetType() override {
			return ChunkType::DATA;
		}

		utils::DataAccessor GetData() {
			return _data_accessor.make_reference();
		}

		utils::DataAccessor GetSerializeData() {
			return _data_out_accessor.make_reference();
		}

		bool Decode() override {
			_data_accessor = (_accessor + 8).deep_copy(GetActualDataSize());
			return true;
		}

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;

		utils::DataAccessor AllocateSerializeData(size_t out_size) {
			_data_out_accessor = utils::DataAccessor::Alloc(out_size);
			return _data_out_accessor.make_reference();
		}

		void SetTrueAllocatedSize(size_t size) {
			_data_out_accessor.size = size;
		}

	private:
		utils::DataAccessor _data_accessor;
		utils::DataAccessor _data_out_accessor;
	};

	class hkDataChunkTYPE : public hkDataChunkTAG0 {
	public:
		hkDataChunkTYPE(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = 0x00;
			type_name[0] = 'T';
			type_name[1] = 'Y';
			type_name[2] = 'P';
			type_name[3] = 'E';
		}
		~hkDataChunkTYPE() {
		}

		ChunkType GetType() override {
			return ChunkType::TYPE;
		}

		bool Decode() override {
			return true;
		}

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTPTR : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPTR(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'P';
			type_name[2] = 'T';
			type_name[3] = 'R';
		}
		~hkDataChunkTPTR() {
		}

		ChunkType GetType() override {
			return ChunkType::TPTR;
		}

		bool Decode() override {
			return true;
		}

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTST1(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'S';
			type_name[2] = 'T';
			type_name[3] = '1';
		}
		~hkDataChunkTST1() {
		}

		ChunkType GetType() override {
			return ChunkType::TST1;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTNA1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTNA1(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'N';
			type_name[2] = 'A';
			type_name[3] = '1';
		}
		~hkDataChunkTNA1() {
		}

		ChunkType GetType() override {
			return ChunkType::TNA1;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkFST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkFST1(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'F';
			type_name[1] = 'S';
			type_name[2] = 'T';
			type_name[3] = '1';
		}
		~hkDataChunkFST1() {
		}

		ChunkType GetType() override {
			return ChunkType::FST1;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTBDY : public hkDataChunkTAG0 {
	public:
		hkDataChunkTBDY(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'B';
			type_name[2] = 'D';
			type_name[3] = 'Y';
		}
		~hkDataChunkTBDY() {
		}

		ChunkType GetType() override {
			return ChunkType::TBDY;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTHSH : public hkDataChunkTAG0 {
	public:
		hkDataChunkTHSH(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'H';
			type_name[2] = 'S';
			type_name[3] = 'H';
		}
		~hkDataChunkTHSH() {
		}

		ChunkType GetType() override {
			return ChunkType::THSH;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkTPAD : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPAD(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'T';
			type_name[1] = 'P';
			type_name[2] = 'A';
			type_name[3] = 'D';
		}
		~hkDataChunkTPAD() {
		}

		ChunkType GetType() override {
			return ChunkType::TPAD;
		}

		bool Decode() override {
			return true;
		}

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkINDX : public hkDataChunkTAG0 {
	public:
		hkDataChunkINDX(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = 0x00;
			type_name[0] = 'I';
			type_name[1] = 'N';
			type_name[2] = 'D';
			type_name[3] = 'X';
		}
		~hkDataChunkINDX() {
		}

		ChunkType GetType() override {
			return ChunkType::INDX;
		}

		bool Decode() override {
			return true;
		}
	};

	class hkDataChunkITEM : public hkDataChunkTAG0 {
	public:
		hkDataChunkITEM(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'I';
			type_name[1] = 'T';
			type_name[2] = 'E';
			type_name[3] = 'M';
		}
		~hkDataChunkITEM() {
		}

		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks; // No ownership

		ChunkType GetType() override {
			return ChunkType::ITEM;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	class hkDataChunkPTCH : public hkDataChunkTAG0 {
	public:
		hkDataChunkPTCH(hkReflDataSerializeContext* owner) : hkDataChunkTAG0(owner) {
			chunk_decorator = _leaf_decorator;
			type_name[0] = 'P';
			type_name[1] = 'T';
			type_name[2] = 'C';
			type_name[3] = 'H';
		}
		~hkDataChunkPTCH() {
		}

		ChunkType GetType() override {
			return ChunkType::PTCH;
		}

		bool Decode() override;

		uint64_t Serialize(utils::DataAccessor& out, bool use_cached = false) override;
	};

	hkDataChunkBase* AllocateChunk(ChunkType type, hkReflDataSerializeContext* ref_data);
}