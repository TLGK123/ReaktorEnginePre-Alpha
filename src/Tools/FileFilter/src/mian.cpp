#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <io.h>
#include <stdlib.h>

using namespace std;

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::vector<std::string> files;

void listFiles(const char * dir)
{
	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			//cout << dir << "\\" << findData.name << "\t<dir>\n";

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);
		}
		else
		{
			//cout << dir << "\\" << findData.name << "\t" << findData.size << " b\n";
			//char path_buffer[_MAX_PATH];
			//char drive[_MAX_DRIVE];
			//char dir[_MAX_DIR];
			//char fname[_MAX_FNAME];
			//char ext[_MAX_EXT];

			//string s = string(dir) + string(findData.name);
			//strcpy(path_buffer, s.c_str());
			//_splitpath(path_buffer, drive, dir, fname, ext);

			//cout<< ext <<endl;
			//delete ext, path_buffer, drive, fname, dir;
			//;
			files.push_back(s);
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // 关闭搜索句柄
}

int main(int argc, char const *argv[])
{
	map<string, string> commands;
	vector<string> filters;
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			commands.insert(pair<string, string>(argv[i], argv[i + 1]));
		}
	}
	filters = split(commands["-f"], ' ');

	listFiles(commands["-p"].c_str());
	//cout << "Path " << commands["-p"] << endl;
	//cout << "filter " << commands["-f"] << endl;

	vector<string>::iterator iter;
	for (iter = files.begin(); iter != files.end(); iter++)
	{
		cout << *iter << endl;
	}
	;
	return 0;
}