#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hknpShape;
	class hknpRefDragProperties;
	class hkLocalFrame;
	class hknpRefMassDistribution;
	class hkRefCountedProperties;

	template <typename tTYPE>
	class hkRefPtr;
	template<>
	class hkRefPtr<hknpShape> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hknpShape>"; };
		inline uint32_t GethkClassHash() override { return 3635148273; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRefPtr<hknpRefMassDistribution> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hknpRefMassDistribution>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRefPtr<hknpRefDragProperties> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hknpRefDragProperties>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRefPtr<hkLocalFrame> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hkLocalFrame>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRefPtr<hkReferencedObject> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hkReferencedObject>"; };
		inline uint32_t GethkClassHash() override { return 2363435676; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkRefPtr<hkRefCountedProperties> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefPtr"; };
		inline std::string GetTranscriptId() override { return "hkRefPtr<hkRefCountedProperties>"; };
		inline uint32_t GethkClassHash() override { return 2830703274; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
