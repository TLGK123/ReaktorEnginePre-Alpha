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

#include "FileSystem.h"

using namespace std;

namespace TmingEngine
{
	string FileSystem::getPath(std::string assetpath)
	{
		char buffer[MAX_PATH];
		getcwd(buffer, MAX_PATH);
		std::string path = buffer;
		std::string name = "TmingEngine";
		int cutIndex = path.find(name);

		std::string  temp = path.substr(0, cutIndex + name.length());
		if (assetpath.length() > 0)
		{
			path = temp + "/" + assetpath;
		}
		else
		{
			path = temp;
		}

		string s = "AssetPath: " + path + "\n";
		//Debug::Log(s.c_str());
		return path;
	}

	void FileSystem::SaveFile(string path, string content)
	{
		ofstream fout(path);
		if (!fout)return;
		fout << content << endl;
		fout.close();
	}

	string FileSystem::GetFileContent(string f)
	{
		string content;
		ifstream fin(f);
		string  s;
		while (getline(fin, s))
		{
			content += s + "\n";
		}
		fin.close();
		return content;
	}
}