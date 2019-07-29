#pragma once
#include "Core/SubSystem.h"
#include <chrono>
#include <iostream>
#include <list>
#include <string>

//====================

namespace TmingEngine
{
	static class ENGINE_CLASS Debug : public Subsystem
	{
	public:
		static void Log(const char * message, ...);
        static void Log(std::string msg);
	private:
	};
}
