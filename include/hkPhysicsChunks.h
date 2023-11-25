#pragma once
#include "Common.h"
#include "hkReflection.h"
#include "hkPhysics.h"

namespace hkreflex {
	class hkClassBase;
	class hkIndexedDataBlock;
}

namespace hkphysics {
	class hkPhysicsReflectionData;

	enum class ChunkType {
		Unknown = -1,
		TAG0, // Major data chunk
		SDKV, // SDK version
		DATA, // Data
		TYPE, // Types
		TPTR, // Type pointer
		TST1, // Type names
		TNA1, // Unknown type info
		FST1, // Field names
		TBDY, // Type body
		THSH, // Type hash
		TPAD, // Type padding
		INDX, // Index
		ITEM, // Item
		PTCH, // Patch
	};

	std::string_view GetChunkTypeName(ChunkType type);

	ChunkType ChunkTypeFromName(const std::string name);

	class hkDataChunkBase {
	public:
		hkDataChunkBase(hkPhysicsReflectionData* owner): ref_data(owner) {
		}
		~hkDataChunkBase() {
		}
		hkPhysicsReflectionData* ref_data = nullptr;
		uint16_t chunk_decorator = -1;
		uint16_t data_size = 0;
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

		static const uint16_t _leaf_decorator = 0x4000;

		utils::DataAccessor GetBuffer() {
			return _accessor;
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

		virtual bool Serialize(uint8_t*& out, bool use_cached = false) {
			if (use_cached && _own_buffer) {
				std::memcpy(out, _accessor.data, _accessor.size);
				return true;
			}
			return false;
		}

	protected:
		bool _own_buffer = false;
		utils::DataAccessor _accessor;
	};

	class hkDataChunkTAG0 :public hkDataChunkBase {
	public:
		hkDataChunkTAG0(hkPhysicsReflectionData* owner) : hkDataChunkBase(owner) {
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

	};

	class hkDataChunkSDKV : public hkDataChunkTAG0 {
	public:
		hkDataChunkSDKV(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkSDKV() {
		}

		ChunkType GetType() override {
			return ChunkType::SDKV;
		}

		bool Decode() override;
	};

	class hkDataChunkDATA : public hkDataChunkTAG0 {
	public:
		hkDataChunkDATA(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkDATA() {
		}

		ChunkType GetType() override {
			return ChunkType::DATA;
		}

		utils::DataAccessor GetData() {
			return _data_accessor;
		}

		utils::DataAccessor GetSerializeData() {
			return _data_out_accessor;
		}

		bool Decode() override {
			_data_accessor = (_accessor + 8).deep_copy(GetActualDataSize());
			return true;
		}

	private:
		utils::DataAccessor _data_accessor;
		utils::DataAccessor _data_out_accessor;
	};

	class hkDataChunkTYPE : public hkDataChunkTAG0 {
	public:
		hkDataChunkTYPE(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTYPE() {
		}

		ChunkType GetType() override {
			return ChunkType::TYPE;
		}

		bool Decode() override {
			return true;
		}

		bool Serialize(uint8_t*& out, bool use_cached = false) override;
	};

	class hkDataChunkTPTR : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPTR(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTPTR() {
		}

		ChunkType GetType() override {
			return ChunkType::TPTR;
		}

		bool Decode() override {
			return true;
		}
	};

	class hkDataChunkTST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTST1(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTST1() {
		}

		ChunkType GetType() override {
			return ChunkType::TST1;
		}

		bool Decode() override;
	};

	class hkDataChunkTNA1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTNA1(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTNA1() {
		}

		ChunkType GetType() override {
			return ChunkType::TNA1;
		}

		bool Decode() override;
	};

	class hkDataChunkFST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkFST1(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkFST1() {
		}

		ChunkType GetType() override {
			return ChunkType::FST1;
		}

		bool Decode() override;
	};

	class hkDataChunkTBDY : public hkDataChunkTAG0 {
	public:
		hkDataChunkTBDY(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTBDY() {
		}

		ChunkType GetType() override {
			return ChunkType::TBDY;
		}

		bool Decode() override;
	};

	class hkDataChunkTHSH : public hkDataChunkTAG0 {
	public:
		hkDataChunkTHSH(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTHSH() {
		}

		ChunkType GetType() override {
			return ChunkType::THSH;
		}

		bool Decode() override;
	};

	class hkDataChunkTPAD : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPAD(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkTPAD() {
		}

		ChunkType GetType() override {
			return ChunkType::TPAD;
		}

		bool Decode() override {
			return true;
		}
	};

	class hkDataChunkINDX : public hkDataChunkTAG0 {
	public:
		hkDataChunkINDX(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
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
		hkDataChunkITEM(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkITEM() {
		}

		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks; // No ownership

		ChunkType GetType() override {
			return ChunkType::ITEM;
		}

		bool Decode() override;

		bool Serialize(uint8_t*& out, bool use_cached = false) override;
	};

	class hkDataChunkPTCH : public hkDataChunkTAG0 {
	public:
		hkDataChunkPTCH(hkPhysicsReflectionData* owner) : hkDataChunkTAG0(owner) {
		}
		~hkDataChunkPTCH() {
		}

		ChunkType GetType() override {
			return ChunkType::PTCH;
		}

		bool Decode() override {
			return true;
		}
	};

	hkDataChunkBase* AllocateChunk(ChunkType type, hkPhysicsReflectionData* ref_data);
}