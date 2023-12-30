#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include <json.hpp>
// Finished

namespace hktypes {
	class hkHolderBase;
	class hkReferencedObject;

	class hkQsTransformf : public hkHolderBase {
	public:
		using BaseType = void;
		// From hkQsTransform
		Eigen::Vector4f translation;
		Eigen::Quaternionf rotation;
		Eigen::Vector4f scale;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hkQsTransformf"; };
		inline std::string GetTranscriptId() { return "hkQsTransformf"; };
		inline uint32_t GethkClassHash() { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "translation", "hkVector4f" },
				{ "rotation", "hkQuaternionf" },
				{ "scale", "hkVector4f" },
			};
		};

		Eigen::Matrix4f getMatrix(bool force_M44_1 = false);

		static Eigen::Vector4f getRotatedDir(Eigen::Vector4f& dir, Eigen::Quaternionf& rot);
		static hkQsTransformf fromMultiplied(hkQsTransformf& a, hkQsTransformf& b);
		static hkQsTransformf fromInverse(hkQsTransformf& a);
		static hkQsTransformf fromMatrix(Eigen::Matrix4f& mat, float scale = 1);
	};

	class hkQsTransform : public hkQsTransformf {
	public:
		using BaseType = hkQsTransformf;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hkQsTransform"; };
		inline std::string GetTranscriptId() { return "hkQsTransform"; };
		inline uint32_t GethkClassHash() { return 973428694; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
			};
		};
	};

	class hkaBoneHolder : public hkHolderBase {
	public:
		using BaseType = void;
		// From hkaBone
		std::string name;
		bool lockTranslation = false;

		// From hkaSkeleton
		hkaBoneHolder* parent = nullptr;

		// Extra
		std::vector<hkaBoneHolder*> children;
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hkaBone"; };
		inline std::string GetTranscriptId() { return "hkaBone"; };
		inline uint32_t GethkClassHash() { return 704422420; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "name", "hkStringPtr" },
				{ "lockTranslation", "hkBool" },
			};
		};

		void SetTransform(hkQsTransformf& transform, bool update_world_trans = true);

		void SetWorldTransform(hkQsTransformf& transform, bool update_local_trans = true);

		hkQsTransformf GetTransform();

		hkQsTransformf GetWorldTransform();

	protected:
		hkQsTransformf transform;
		hkQsTransformf world_transform;
	};

	class hkaSkeleton : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		std::string name;
		hkaBoneHolder* root = nullptr;
		std::vector<hkaBoneHolder*> bones;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hkaSkeleton"; };
		inline std::string GetTranscriptId() { return "hkaSkeleton"; };
		inline uint32_t GethkClassHash() { return 2607764882; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "name", "hkStringPtr" },
				{ "parentIndices", "hkArray<hkInt16, hkContainerHeapAllocator>" },
				{ "bones", "hkArray<hkaBone, hkContainerHeapAllocator>" },
				{ "referencePose", "hkArray<hkQsTransform, hkContainerHeapAllocator>" },
				{ "referenceFloats", "hkArray<hkReal, hkContainerHeapAllocator>" },
				{ "floatSlots", "hkArray<hkStringPtr, hkContainerHeapAllocator>" },
				{ "localFrames", "hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator>" },
				{ "partitions", "hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator>" },
			};
		};

		void TraverseBones(std::function<bool(hkaBoneHolder*)> pre_order_func, std::function<bool(hkaBoneHolder*)> post_order_func = [](hkaBoneHolder*)->bool { return true; });

		nlohmann::json ToJson(hkaBoneHolder* bone = nullptr);

		void FromJson(nlohmann::json& json, hkaBoneHolder* bone = nullptr);

		uint16_t GetBoneIndex(std::string bone_name);

		hkaBoneHolder* GetBone(std::string bone_name);

		hkaSkeleton* Clone();

	protected:
		void CalculateBoneList();
	};
}