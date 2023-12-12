#pragma once
#include "hkInclude.h"
#include "json.hpp"

namespace hktypes {
	class hkHolderBase;
	class hclSimClothData;
	class hclObjectSpaceSkinPNOperator;
	class hclBoneSpaceSkinPNOperator;

	class hkPackedVector3 : public hkHolderBase {
	public:
		int16_t values[4];

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Vector3f ToVector3f();
		static hkPackedVector3 FromVector3f(const Eigen::Vector3f vec);
	};

	class hkVector4Holder : public hkHolderBase {
	public:
		float values[4];

		// Extra
		hkVector4Holder() = default;
		hkVector4Holder(float x, float y, float z, float w) {
			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}

		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Vector4f ToVector4f();
		static hkVector4Holder FromVector4f(const Eigen::Vector4f vec);

		Eigen::Vector3f ToVector3f();
		static hkVector4Holder FromVector3f(const Eigen::Vector3f vec);
	};

	class hkMatrix4Holder : public hkHolderBase {
	public:
		float values[16];

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
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
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	template<class tStorage>
	class hkBitFieldBase : public hkHolderBase {
	public:
		tStorage storage;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hkBitField : public hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>> {
	public:
		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
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
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hkRootLevelContainer::NamedVariant> namedVariants;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		hkReferencedObject* GetNamedVariantRef(std::string type_name, std::string instance_name = "");
	};

	class hclBufferedMeshObj {
	public:
		using BoneWeightPair = std::pair<uint16_t, uint8_t>;
		using BoneWeightList = std::vector<BoneWeightPair>;

		class ExtraDataBase {
		public:
			std::string name;
		};

		template<class tStorage>
		requires utils::_is_bool_t<tStorage> || utils::_is_integer_t<tStorage> || utils::_is_float_t<tStorage> || utils::_is_string_t<tStorage> || hktypes::_is_hk_holder_t<tStorage>
		class ExtraData : public ExtraDataBase {
		public:
			tStorage data;
		};

		enum ShapeType :uint8_t {
			Mesh = 0,
			Capsule = 1,
		};

		std::string name;
		ShapeType shapeType = ShapeType::Mesh;

		Eigen::Matrix4f localFrame = Eigen::Matrix4f::Identity();

		// Per-vertex data
		std::vector<std::array<float, 3>> positions;
		std::vector<std::array<float,3>> normals;
		std::vector<BoneWeightList> boneWeights;
		std::vector<std::vector<ExtraDataBase*>> extraDataList;

		// Per-triangle data
		std::vector<std::vector<uint32_t>> triangleIndices;

		// Extra shapes
		std::vector<hclBufferedMeshObj> extraShapes;

		// Capsule properties
		std::array<float, 3> capsuleStart;
		std::array<float, 3> capsuleEnd;
		float capsuleBigRadius;
		float capsuleSmallRadius;

		template<class tStorage>
		requires utils::_is_bool_t<tStorage> || utils::_is_integer_t<tStorage> || utils::_is_float_t<tStorage> || utils::_is_string_t<tStorage> || hktypes::_is_hk_holder_t<tStorage>
		static ExtraData<tStorage>*make_extra_data(std::string name, const tStorage& data) {
			auto extra_data = new ExtraData<tStorage>();
			extra_data->name = name;
			extra_data->data = data;
			return extra_data;
		}

		hclBufferedMeshObj& FromSimClothData(hclSimClothData* simClothData);
		hclBufferedMeshObj& FromObjectSpaceSkinPNOperator(hclObjectSpaceSkinPNOperator* skinOperator);
		hclBufferedMeshObj& FromBoneSpaceSkinPNOperator(hclBoneSpaceSkinPNOperator* skinOperator);

		nlohmann::json ToJson();
	};

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	class hkHandle : public hkHolderBase {
	public:
		tStorage value = -1;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	template<class tStorage>
	inline bool hkBitFieldStorage<tStorage>::FromInstance(const hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
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
	inline bool hkBitFieldBase<tStorage>::FromInstance(const hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
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
	inline bool hkHandle<tStorage>::FromInstance(const hkreflex::hkClassInstance* instance)
	{
		auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
		if (instance->type->type_name != "hkHandle") {
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
		if (instance->type->type_name != "hkHandle") {
			std::cout << "hkHandle::FromInstance: Wrong type! Expect: hkHandle, Get: " << instance->type->type_name << std::endl;
			return false;
		}

		class_instance->GetInstanceByFieldName("value")->SetValue(value);

		return true;
	}
}