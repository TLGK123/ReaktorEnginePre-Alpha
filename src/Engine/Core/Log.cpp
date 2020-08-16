/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Log.h"
using namespace std;
namespace TmingEngine
{
	void Debug::Log(const char* message, ...)
	{
		std::cout << message << std::endl;
		//printf(message);
		//Global<Context>().GetSubsystem<Console>()->AddLog(message);
	}

	void Debug::Log(string msg)
	{
		std::cout << msg << std::endl;
		// printf(msg.c_str());
		 //Global<Context>().GetSubsystem<Console>()->AddLog(message);
	}

	void Debug::Log(glm::mat4 m)
	{
		char tempBuffer[200];
		sprintf(tempBuffer, "\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f\n", m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
		printf(string(tempBuffer).c_str());
	}
}