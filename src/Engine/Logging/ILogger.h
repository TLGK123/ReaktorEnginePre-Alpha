

#pragma once

//= INCLUDES ==============
#include <string>
#include "../Core/EngineDefs.h"
//=========================

namespace TmingEngine
{
	enum LogType
	{
		Error,
	    Assert,
		Warning,
		Log,
		Exception
	};

	class ENGINE_CLASS ILogger
	{
	public:
		virtual ~ILogger() {}
		virtual void Log(const std::string& log, int type) = 0;
		virtual bool IsLogTypeAllowed() { return true; };
	};
}
