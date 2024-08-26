#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;
	class hkFloat3;
	class hknpConvexHull::Edge;
	class hknpConvexHull::Face;

	template <typename tT>
	class hkRelArray;
	template<>
	class hkRelArray<hkFloat3> : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt32 offset; // Offset: 0
		int size; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRelArray"; };
		inline std::string GetTranscriptId() override { return "hkRelArray<hkFloat3>"; };
		inline uint32_t GethkClassHash() override { return 2425848652; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "offset", "hkInt32" },
				{ "size", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRelArray<hkVector4> : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt32 offset; // Offset: 0
		int size; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRelArray"; };
		inline std::string GetTranscriptId() override { return "hkRelArray<hkVector4>"; };
		inline uint32_t GethkClassHash() override { return 4050892480; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "offset", "hkInt32" },
				{ "size", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRelArray<hknpConvexHull::Face> : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt32 offset; // Offset: 0
		int size; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRelArray"; };
		inline std::string GetTranscriptId() override { return "hkRelArray<hknpConvexHull::Face>"; };
		inline uint32_t GethkClassHash() override { return 2364447659; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "offset", "hkInt32" },
				{ "size", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRelArray<hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt32 offset; // Offset: 0
		int size; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRelArray"; };
		inline std::string GetTranscriptId() override { return "hkRelArray<hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 3140512678; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "offset", "hkInt32" },
				{ "size", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRelArray<hknpConvexHull::Edge> : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt32 offset; // Offset: 0
		int size; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRelArray"; };
		inline std::string GetTranscriptId() override { return "hkRelArray<hknpConvexHull::Edge>"; };
		inline uint32_t GethkClassHash() override { return 2111480292; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "offset", "hkInt32" },
				{ "size", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
