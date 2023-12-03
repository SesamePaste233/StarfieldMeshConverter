#pragma once
#include <type_traits>
#include "Common.h"
#include "hkReflection.h"
#include "json.hpp"

#include "hkaSkeleton.h"
#include "hclSimClothData.h"
#include "hclClothData.h"

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

	class hkReferencedObject : public hkHolderBase {
	};

	class hkPackedVector3Holder : public hkHolderBase {
	public:
		int16_t values[4];

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

		Eigen::Vector3f ToVector3f();
		static hkPackedVector3Holder FromVector3f(const Eigen::Vector3f vec);
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
}