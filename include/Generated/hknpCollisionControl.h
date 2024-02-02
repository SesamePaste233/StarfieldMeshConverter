#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tBITS, typename tSTORAGE>
	class ;

	class hknpCollisionControl : public hkFlags<hknpCollisionControl::Enum, unsigned short> {
	public:
		using BaseType = hkFlags<hknpCollisionControl::Enum, unsigned short>;
		class Enum : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpCollisionControl::Enum"; };
			inline std::string GetTranscriptId() override { return "hknpCollisionControl::Enum"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};


		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCollisionControl"; };
		inline std::string GetTranscriptId() override { return "hknpCollisionControl"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
