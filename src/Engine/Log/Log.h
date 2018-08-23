#pragma once
#include "Core/SubSystem.h"
#include <chrono>
#include <iostream>
#include <list>
#include "../Editor/Console.h"
#include "Core/SmartPtr.h"
#include "../Editor/Screen.h"
#include "Core/Context.h"
//====================

namespace TmingEngine
{
	static class ENGINE_CLASS Debug : public Subsystem
	{
	public:
		static void Log(const char * message, ...);
	private:
	};
}