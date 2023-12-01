#pragma once
#include <type_traits>
#include "Common.h"
#include "hkReflection.h"
#include "json.hpp"

namespace hkphysics {
	class hkPhysicsReflectionData;
}

namespace hkreflex {
	class hkClassBase;
	class hkClassInstance;
}

namespace hktypes {

	class hkHolderBase {
	public:
		virtual bool FromInstance(hkreflex::hkClassInstance* instance) = 0;
		virtual bool ToInstance(hkreflex::hkClassInstance* instance) = 0;
	};

	class hkQsTransform : public hkHolderBase {
	public:
		// From hkQsTransform
		Eigen::Vector4f translation;
		Eigen::Quaternionf rotation;
		Eigen::Vector4f scale;

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Matrix4f getMatrix(bool force_M44_1 = false);

		static Eigen::Vector4f getRotatedDir(Eigen::Vector4f& dir, Eigen::Quaternionf& rot);
		static hkQsTransform fromMultiplied(hkQsTransform& a, hkQsTransform& b);
	};

	class hkaBoneHolder : public hkHolderBase {
	public:
		// From hkaBone
		std::string name;
		bool lock_translation = false;

		// From hkaSkeleton
		hkaBoneHolder* parent = nullptr;
		hkQsTransform transform;
		hkQsTransform world_transform;

		// Extra
		std::vector<hkaBoneHolder*> children;
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hkaSkeletonHolder : public hkHolderBase {
	public:
		std::string name;
		hkaBoneHolder* root = nullptr;

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		void TraverseBones(std::function<void(hkaBoneHolder*)> pre_order_func, std::function<void(hkaBoneHolder*)> post_order_func);

		nlohmann::json ToJson(hkaBoneHolder* bone = nullptr);
	};
}