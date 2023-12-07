#pragma once
#include "hkInclude.h"

namespace hktypes {
	class hkHolderBase;

	class hkPackedVector3 : public hkHolderBase {
	public:
		int16_t values[4];

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Vector3f ToVector3f();
		static hkPackedVector3 FromVector3f(const Eigen::Vector3f vec);
	};

	class hkVector4Holder : public hkHolderBase {
	public:
		float values[4];

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Vector4f ToVector4f();
		static hkVector4Holder FromVector4f(const Eigen::Vector4f vec);
	};

	class hkMatrix4Holder : public hkHolderBase {
	public:
		float values[16];

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Matrix4f ToMatrix4f();
		static hkMatrix4Holder FromMatrix4f(const Eigen::Matrix4f mat);
	};

	template<class tStorage>
	class hkBitFieldStorage : public hkHolderBase {
	public:
		tStorage words;	// Offset: 0 Unk: 0
		int numBits;	// Offset: 16 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	template<class tStorage>
	class hkBitFieldBase : public hkHolderBase {
	public:
		tStorage storage;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hkBitField : public hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>> {
	public:
		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		std::vector<bool> GetMask();
		void SetMask(std::vector<bool>& mask);
	};

	class hkRootLevelContainer : public hkHolderBase {
	public:
		class NamedVariant : public hkHolderBase {
		public:
			std::string name;	// Offset: 0 Unk: 0
			std::string className;	// Offset: 8 Unk: 0
			hkReferencedObject* variant;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hkRootLevelContainer::NamedVariant> namedVariants;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		hkReferencedObject* GetNamedVariantRef(std::string type_name, std::string instance_name = "");
	};

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	class hkHandle : public hkHolderBase {
	public:
		tStorage value = -1;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	template<class tStorage>
	inline bool hkBitFieldStorage<tStorage>::FromInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (class_instance->type->type_name != "hkBitFieldStorage") {
			std::cout << "hkBitFieldStorage::FromInstance: Wrong type!" << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("words")->GetValue(words);
		class_instance->GetInstanceByFieldName("numBits")->GetValue(numBits);
		return true;
	}

	template<class tStorage>
	inline bool hkBitFieldStorage<tStorage>::ToInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (class_instance->type->type_name != "hkBitFieldStorage") {
			std::cout << "hkBitFieldStorage::FromInstance: Wrong type!" << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("words")->SetValue(words);
		class_instance->GetInstanceByFieldName("numBits")->SetValue(numBits);
		return true;
	}

	template<class tStorage>
	inline bool hkBitFieldBase<tStorage>::FromInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (class_instance->type->type_name != "hkBitFieldBase") {
			std::cout << "hkBitFieldBase::FromInstance: Wrong type!" << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
		return true;
	}

	template<class tStorage>
	inline bool hkBitFieldBase<tStorage>::ToInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (class_instance->type->type_name != "hkBitFieldBase") {
			std::cout << "hkBitFieldBase::FromInstance: Wrong type!" << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
		return true;
	}

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	inline bool hkHandle<tStorage>::FromInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (instance->type->type_name != "hkHandle" || class_instance == nullptr) {
			std::cout << "hkHandle::FromInstance: Wrong type! Expect: hkHandle, Get: " << instance->type->type_name << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("value")->GetValue(value);

		return true;
	}

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	inline bool hkHandle<tStorage>::ToInstance(hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
		if (instance->type->type_name != "hkHandle" || class_instance == nullptr) {
			std::cout << "hkHandle::FromInstance: Wrong type! Expect: hkHandle, Get: " << instance->type->type_name << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("value")->SetValue(value);

		return true;
	}
}