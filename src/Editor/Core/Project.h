#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#ifdef __APPLE__
#include <sys/uio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <io.h>
#endif
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <string>

#include "TextEditor.h"

namespace TmingEngine
{
	class Project :public Widget
	{
	public:

		Project(Context *context)
		{
			m_title = "Project";
		}
		~Project();

		void Begin();
		void Update();
		void End();

		std::vector<std::string> FileFilter(const char * dir , std::vector<std::string> filefilters);
		
	};
}
