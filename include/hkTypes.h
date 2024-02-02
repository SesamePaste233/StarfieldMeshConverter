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
		using BaseType = void;
		int16_t values[4] = { 0,0,0,0 };

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkPackedVector3"; };
		inline std::string GetTranscriptId() override { return "hkPackedVector3"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "values", "T[N]<hkInt16, 4>" },
			};
		};

		Eigen::Vector3f ToVector3f();
		static hkPackedVector3 FromVector3f(const Eigen::Vector3f vec);
	};

	class hkVector4Holder : public hkHolderBase {
	public:
		using BaseType = void;
		float values[4] = { 0,0,0,0 };

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
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};

		Eigen::Vector4f ToVector4f();
		static hkVector4Holder FromVector4f(const Eigen::Vector4f vec);

		Eigen::Vector3f ToVector3f();
		static hkVector4Holder FromVector3f(const Eigen::Vector3f vec, const float w = 0);
	};

	class hkMatrix4Holder : public hkHolderBase {
	public:
		using BaseType = void;
		float values[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};

		Eigen::Matrix4f ToMatrix4f();
		static hkMatrix4Holder FromMatrix4f(const Eigen::Matrix4f mat);
	};

	template<class tStorage>
	class hkBitFieldStorage : public hkHolderBase {
	public:
		using BaseType = void;
		tStorage words;	// Offset: 0 Unk: 0
		int numBits = 0;	// Offset: 16 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
	};

	template<class tStorage>
	class hkBitFieldBase : public hkHolderBase {
	public:
		using BaseType = void;
		tStorage storage;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
	};

	class hkBitField : public hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>> {
	public:
		using BaseType = hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>>;
		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};

		hkBitField() = default;
		hkBitField(std::vector<bool>& mask, int num_bits) {
			FromMask(mask, num_bits);
		}
		hkBitField(std::vector<uint32_t>& ids, int num_bits) {
			FromMaskedIds(ids, num_bits);
		}

		hkBitField FromMask(std::vector<bool>& mask, int num_bits);
		hkBitField FromMaskedIds(std::vector<uint32_t>& ids, int num_bits);

		std::vector<bool> GetMask();
		std::vector<uint32_t> GetMaskedIds();
		void SetMask(std::vector<bool>& mask);
		void SetMaskedIds(std::vector<uint32_t>& ids);
		inline void SetNumBits(int num_bits) {
			storage.numBits = num_bits;
			storage.words.resize((num_bits + 31) / 32);
		}
		inline int GetNumBits() {
			return storage.numBits;
		}

		void operator=(const hkBitField& other);

		hkBitField operator|(const hkBitField& other) const;

		hkBitField operator|=(const hkBitField& other);
	};

	class hkRootLevelContainer : public hkHolderBase {
	public:
		using BaseType = void;
		class NamedVariant : public hkHolderBase {
		public:
			using BaseType = void;
			std::string name;	// Offset: 0 Unk: 0
			std::string className;	// Offset: 8 Unk: 0
			hkReferencedObject* variant;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkRootLevelContainer::NamedVariant"; };
			inline std::string GetTranscriptId() override { return "hkRootLevelContainer::NamedVariant"; };
			inline uint32_t GethkClassHash() override { return 2807201; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "name", "hkStringPtr" },
					{ "className", "hkStringPtr" },
					{ "variant", "hkRefVariant" },
				};
			};
		};

		std::vector<hkRootLevelContainer::NamedVariant> namedVariants;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRootLevelContainer"; };
		inline std::string GetTranscriptId() override { return "hkRootLevelContainer"; };
		inline uint32_t GethkClassHash() override { return 54921221; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return { {"namedVariants", "hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator>"} };
		};

		hkReferencedObject* GetNamedVariantRef(std::string type_name, std::string instance_name = "");
		std::vector<hkReferencedObject*> GetNamedVariantRefs(std::string type_name, std::string instance_name = "");
		NamedVariant& GetNamedVariant(std::string type_name, std::string instance_name = "");
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
		std::vector<std::array<float, 3>> normals;
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

		bool ToSimClothData(hclSimClothData* simClothData);
		bool ToObjectSpaceSkinPNOperator(hclObjectSpaceSkinPNOperator* skinOperator);
		bool ToBoneSpaceSkinPNOperator(hclBoneSpaceSkinPNOperator* skinOperator);

		nlohmann::json ToJson();
		hclBufferedMeshObj FromJson(nlohmann::json& json);
	};

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	class hkHandle : public hkHolderBase {
	public:
		using BaseType = void;
		tStorage value = -1;	// Offset: 0 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkHandle"; };
		inline std::string GetTranscriptId() override { return "hkHandle<hkUint32, 2147483647>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "value", "hkUint32" },
			};
		};
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

	//template<class T>
	//requires hktypes::_is_hk_holder_t<T>
	//void GethkClassDefinitions(std::map<std::string, hkreflex::hkClassBase*>& class_map) {
	//	std::string hk_class_name = T::GethkClassName();
	//	bool has_parent = false;
	//	if (class_map.find(hk_class_name) == class_map.end()) { // if not defined
	//		using BaseType = typename T::BaseType;
	//		has_parent = std::is_same_v<BaseType, T>;
	//		if (has_parent) {
	//			class_map[BaseType::GethkClassName()] = new hkreflex::hkClassBase();
	//		}
	//		class_map[hk_class_name] = new hkreflex::hkClassBase();
	//	}
	//}
}