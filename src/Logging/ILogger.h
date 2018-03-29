
#pragma once

//= INCLUDES ==============
#include <string>
#include "../Core/EngineDefs.h"
//=========================

namespace TmingEngine
{
	class ENGINE_CLASS ILogger
	{
	public:
		virtual ~ILogger() {}
		virtual void Log(const std::string& log, int type) = 0;
	};
}
