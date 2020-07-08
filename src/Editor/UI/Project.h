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

#ifndef TmingEngine_Editor_UI_Project_h
#define TmingEngine_Editor_UI_Project_h

#ifdef __APPLE__
#include <sys/uio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <io.h>
#endif

#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>

#include <Core/Engine.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Core/Log/Log.h"
#include "Plantform/Windows/IWindows.h"
#include "Plantform/Windows/Widget.h"
#include "im.h"
#include "CodeEditor.h"
#include "Selection.hpp"
#include "Preview.hpp"

namespace TmingEngine
{
	enum ProjectStyle
	{
		OneLoyout,
		TwoLayout,
	};

	class Project :public Widget
	{
	public:

		Project(Context* context)
		{
			m_title = "Project";
		}
		~Project();

		void Begin();
		void Update();
		void End();
		std::string rightContent;
		std::vector<std::string> FileFilter(const char* dir, std::vector<std::string> filefilters);
	};
}// namespace TmingEngine

#endif //TmingEngine_Editor_UI_Project_h