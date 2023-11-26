#pragma once
#include <type_traits>
#include "Common.h"
#include "hkReflection.h"

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
	};

	class hkaBoneHolder : public hkHolderBase {
	public:
		// From hkaBone
		std::string name;
		bool lock_translation = false;

		// From hkaSkeleton
		hkaBoneHolder* parent = nullptr;
		hkQsTransform transform;

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
	};
}