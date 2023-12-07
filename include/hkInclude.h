#pragma once
#include "Common.h"

namespace hkreflex {
	class hkClassInstance;
	class hkClassRecordInstance;
}

namespace hktypes {
	class hkHolderBase {
	public:
		virtual bool FromInstance(hkreflex::hkClassInstance* instance) = 0;
		virtual bool ToInstance(hkreflex::hkClassInstance* instance) = 0;
	};

	class hkReferencedObject : public hkHolderBase {
	public:
		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override { return true; };
		bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
	};

	template<typename T>
	concept _is_hk_holder_t = std::is_base_of<hkHolderBase, T>::value;

	template<typename T>
	concept _is_hk_array_holder_t = utils::_is_vector_t<T> && _is_hk_holder_t<typename T::value_type>;

	hkHolderBase* AllocateHolder(hkreflex::hkClassInstance* instance);
};

#include "hkReflection.h"