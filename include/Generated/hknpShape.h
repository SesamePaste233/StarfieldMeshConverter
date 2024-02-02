#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	template <typename tENUM, typename tSTORAGE>
	class ;
	template <typename tENUM, typename tSTORAGE>
	class ;
	template <typename tTYPE>
	class ;
	template <typename tBITS, typename tSTORAGE>
	class ;

	class hknpShape : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class FlagsEnum : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpShape::FlagsEnum"; };
			inline std::string GetTranscriptId() override { return "hknpShape::FlagsEnum"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkFlags<hknpShape::FlagsEnum, hkUint16> flags; // Offset: 24
		hkEnum<hknpShapeType::Enum, hkUint8> type; // Offset: 26
		hkUint8 numShapeKeyBits; // Offset: 27
		hkEnum<hknpCollisionDispatchType::Enum, hkUint8> dispatchType; // Offset: 28
		hkReal convexRadius; // Offset: 32
		hkUint64 userData; // Offset: 40
		hkRefPtr<hkRefCountedProperties> properties; // Offset: 48

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpShape"; };
		inline std::string GetTranscriptId() override { return "hknpShape"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "flags", "hkFlags<hknpShape::FlagsEnum, hkUint16>" },
				{ "type", "hkEnum<hknpShapeType::Enum, hkUint8>" },
				{ "numShapeKeyBits", "hkUint8" },
				{ "dispatchType", "hkEnum<hknpCollisionDispatchType::Enum, hkUint8>" },
				{ "convexRadius", "hkReal" },
				{ "userData", "hkUint64" },
				{ "properties", "hkRefPtr<hkRefCountedProperties>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
