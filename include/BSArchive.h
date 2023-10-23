#pragma once
#include "Common.h"

namespace archive {
	class BSArchive
	{
	public:
		BSArchive() {};
		~BSArchive() = default;

		bool Load(const std::string filename);
	};
}