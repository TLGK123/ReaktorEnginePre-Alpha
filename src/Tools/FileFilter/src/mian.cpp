#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <io.h>

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

void listFiles(const char * dir)
{
	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // ��Ŀ¼�������"\\*.*"���е�һ������

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // ����Ƿ�ɹ�
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			cout << findData.name << "\t<dir>\n";

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);
		}
		else
			cout << findData.name << "\t" << findData.size << " bytes.\n";
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // �ر��������
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
	;
	return 0;
}