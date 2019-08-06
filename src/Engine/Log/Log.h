#pragma once
#include "Core/SubSystem.h"
#include <chrono>
#include <iostream>
#include <list>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//====================

namespace TmingEngine
{
	static class ENGINE_CLASS Debug : public Subsystem
	{
	public:
		static void Log(const char * message, ...);
        static void Log(std::string msg);
        static void Log(glm::mat4 msg);
	private:
	};
}
