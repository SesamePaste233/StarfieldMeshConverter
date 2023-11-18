#pragma once
#include "Common.h"
#include "hkReflection.h"
#include "hkPhysics.h"

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
		FST1, // Member names
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
		hkDataChunkBase() {
		}
		~hkDataChunkBase() {
		}

		uint16_t chunk_decorator = -1;
		uint16_t data_size = 0;
		char type_name[4] = { 0 };

		std::vector<hkDataChunkBase*> children;

		virtual ChunkType GetType() = 0;
		virtual bool Decode(hkPhysicsReflectionData*) = 0;

		void Traverse(std::function<void(hkDataChunkBase*)> pre_order_function = [](hkDataChunkBase*) {}, std::function<void(hkDataChunkBase*)> post_order_function = [](hkDataChunkBase*) {}) {
			pre_order_function(this);
			for (auto child : this->children) {
				child->Traverse(pre_order_function, post_order_function);
			}
			post_order_function(this);
		}

		static const uint16_t _leaf_decorator = 0x4000;
	};

	class hkDataChunkTAG0 :public hkDataChunkBase {
	public:
		hkDataChunkTAG0() {
		}
		~hkDataChunkTAG0() {
		}

		ChunkType GetType() override{
			return ChunkType::TAG0;
		}

		bool Decode(hkPhysicsReflectionData*) override{
			return true;
		}

		const uint8_t* GetBuffer() {
			return _buffer;
		}

		uint32_t GetBufferSize() {
			return _buffer_size;
		}

		uint32_t GetActualDataSize() {
			return data_size - 8;
		}

		void SetBuffer(const uint8_t* buffer, uint32_t buffer_size) {
			_buffer = buffer;
			_buffer_size = buffer_size;
		}

		bool DistributeAndDecode(hkPhysicsReflectionData* physics_data, uint32_t indent = 0);

		void ReleaseBuffer() {
			if (_buffer) {
				delete[] _buffer;
				_buffer = nullptr;
			}
			return;
		}

	protected:
		const uint8_t* _buffer = nullptr; // Release on decoded.
		uint32_t _buffer_size = 0;
	};

	class hkDataChunkSDKV : public hkDataChunkTAG0 {
	public:
		hkDataChunkSDKV() {
		}
		~hkDataChunkSDKV() {
		}

		ChunkType GetType() override {
			return ChunkType::SDKV;
		}

		bool Decode(hkPhysicsReflectionData* data) override;
	};

	class hkDataChunkDATA : public hkDataChunkTAG0 {
	public:
		hkDataChunkDATA() {
		}
		~hkDataChunkDATA() {
		}

		ChunkType GetType() override {
			return ChunkType::DATA;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkTYPE : public hkDataChunkTAG0 {
	public:
		hkDataChunkTYPE() {
		}
		~hkDataChunkTYPE() {
		}

		ChunkType GetType() override {
			return ChunkType::TYPE;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkTPTR : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPTR() {
		}
		~hkDataChunkTPTR() {
		}

		ChunkType GetType() override {
			return ChunkType::TPTR;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkTST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTST1() {
		}
		~hkDataChunkTST1() {
		}

		ChunkType GetType() override {
			return ChunkType::TST1;
		}

		bool Decode(hkPhysicsReflectionData* data) override;
	};

	class hkDataChunkTNA1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkTNA1() {
		}
		~hkDataChunkTNA1() {
		}

		ChunkType GetType() override {
			return ChunkType::TNA1;
		}

		bool Decode(hkPhysicsReflectionData* data) override;
	};

	class hkDataChunkFST1 : public hkDataChunkTAG0 {
	public:
		hkDataChunkFST1() {
		}
		~hkDataChunkFST1() {
		}

		ChunkType GetType() override {
			return ChunkType::FST1;
		}

		bool Decode(hkPhysicsReflectionData* data) override;
	};

	class hkDataChunkTBDY : public hkDataChunkTAG0 {
	public:
		hkDataChunkTBDY() {
		}
		~hkDataChunkTBDY() {
		}

		ChunkType GetType() override {
			return ChunkType::TBDY;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkTHSH : public hkDataChunkTAG0 {
	public:
		hkDataChunkTHSH() {
		}
		~hkDataChunkTHSH() {
		}

		ChunkType GetType() override {
			return ChunkType::THSH;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkTPAD : public hkDataChunkTAG0 {
	public:
		hkDataChunkTPAD() {
		}
		~hkDataChunkTPAD() {
		}

		ChunkType GetType() override {
			return ChunkType::TPAD;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkINDX : public hkDataChunkTAG0 {
	public:
		hkDataChunkINDX() {
		}
		~hkDataChunkINDX() {
		}

		ChunkType GetType() override {
			return ChunkType::INDX;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkITEM : public hkDataChunkTAG0 {
	public:
		hkDataChunkITEM() {
		}
		~hkDataChunkITEM() {
		}

		ChunkType GetType() override {
			return ChunkType::ITEM;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	class hkDataChunkPTCH : public hkDataChunkTAG0 {
	public:
		hkDataChunkPTCH() {
		}
		~hkDataChunkPTCH() {
		}

		ChunkType GetType() override {
			return ChunkType::PTCH;
		}

		bool Decode(hkPhysicsReflectionData*) override {
			return true;
		}
	};

	hkDataChunkBase* AllocateChunk(ChunkType type);
}