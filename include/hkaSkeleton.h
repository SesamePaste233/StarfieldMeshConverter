#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include <json.hpp>
// Finished

namespace hktypes {
	class hkHolderBase;
	class hkReferencedObject;

	class hkQsTransform : public hkHolderBase {
	public:
		// From hkQsTransform
		Eigen::Vector4f translation;
		Eigen::Quaternionf rotation;
		Eigen::Vector4f scale;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Matrix4f getMatrix(bool force_M44_1 = false);

		static Eigen::Vector4f getRotatedDir(Eigen::Vector4f& dir, Eigen::Quaternionf& rot);
		static hkQsTransform fromMultiplied(hkQsTransform& a, hkQsTransform& b);
		static hkQsTransform fromInverse(hkQsTransform& a);
		static hkQsTransform fromMatrix(Eigen::Matrix4f& mat, float scale = 1);
	};

	class hkaBoneHolder : public hkReferencedObject {
	public:
		// From hkaBone
		std::string name;
		bool lock_translation = false;

		// From hkaSkeleton
		hkaBoneHolder* parent = nullptr;

		// Extra
		std::vector<hkaBoneHolder*> children;
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		void SetTransform(hkQsTransform& transform, bool update_world_trans = true);

		void SetWorldTransform(hkQsTransform& transform, bool update_local_trans = true);

		hkQsTransform GetTransform();

		hkQsTransform GetWorldTransform();

	protected:
		hkQsTransform transform;
		hkQsTransform world_transform;
	};

	class hkaSkeleton : public hkReferencedObject {
	public:
		std::string name;
		hkaBoneHolder* root = nullptr;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		void TraverseBones(std::function<void(hkaBoneHolder*)> pre_order_func, std::function<void(hkaBoneHolder*)> post_order_func = [](hkaBoneHolder*)->void {});

		nlohmann::json ToJson(hkaBoneHolder* bone = nullptr);

		void FromJson(nlohmann::json& json, hkaBoneHolder* bone = nullptr);
	};
}