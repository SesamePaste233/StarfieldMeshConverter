#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tBITS, typename tSTORAGE>
	class ;

	class hknpCollisionFlags : public hkFlags<hknpCollisionFlags::Enum, int> {
	public:
		using BaseType = hkFlags<hknpCollisionFlags::Enum, int>;
		class Enum : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpCollisionFlags::Enum"; };
			inline std::string GetTranscriptId() override { return "hknpCollisionFlags::Enum"; };
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
		inline std::string GethkClassName() override { return "hknpCollisionFlags"; };
		inline std::string GetTranscriptId() override { return "hknpCollisionFlags"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
