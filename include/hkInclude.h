#pragma once
#include "Common.h"

namespace hkreflex {
	class hkClassInstance;
	class hkClassRecordInstance;
}

namespace hktypes {
	class hkHolderBase {
	public:
		virtual bool FromInstance(const hkreflex::hkClassInstance* instance) = 0;
		virtual bool ToInstance(hkreflex::hkClassInstance* instance) = 0;
		virtual std::string GethkClassName() = 0;
		virtual std::string GetTranscriptId() = 0;
		virtual uint32_t GethkClassHash() = 0;
		virtual std::vector<std::pair<std::string, std::string>> GethkClassMembers() = 0;
	};

	class hkReferencedObject : public hkHolderBase {
	public:
		using BaseType = void;
		uint64_t sizeAndFlags; // Offset: 8
		uint64_t refCount; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
		bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
		inline std::string GethkClassName() override { return "hkReferencedObject"; };
		inline std::string GetTranscriptId() override { return "hkReferencedObject"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "sizeAndFlags", "hkUlong" },
				{ "refCount", "hkUlong" },
			};
		};
	};

	template<typename T>
	concept _is_hk_holder_t = std::is_base_of<hkHolderBase, T>::value;

	template<typename T>
	concept _is_hk_array_holder_t = utils::_is_vector_t<T> && _is_hk_holder_t<typename T::value_type>;

	hkHolderBase* AllocateHolder(const hkreflex::hkClassInstance* instance);
};

#include "hkReflection.h"