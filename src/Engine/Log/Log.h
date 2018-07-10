#pragma once
#include "Core/SubSystem.h"
#include <chrono>
#include <iostream>
#include <list>
//====================

namespace TmingEngine
{
	typedef void (*HandleLog)(char* Log) ;

	static class ENGINE_CLASS Debug : public Subsystem
	{
	public:
	 static void Log(const char * message,...);

	private:

	
	};
}