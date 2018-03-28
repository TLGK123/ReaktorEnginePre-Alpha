#pragma once
#include<string>
#include "EngineDefs.h"

#define GENERATE_GUID Directus::GUIDGenerator::Generate()

namespace TmingEngine
{
	class ENGINE_CLASS GUIDGenerator
	{
	public:
		static unsigned int Generate();
		static std::string GenerateAsStr();

		static std::string ToStr(unsigned int guid);
		static unsigned int ToUnsignedInt(const std::string& guid);
	};
}