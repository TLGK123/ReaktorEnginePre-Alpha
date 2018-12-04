#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include "FileReader.hpp"
#include "FileFilter.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	int todayWork = 0;
	vector<string> fi({ ".cpp",".cs",".hpp" });
	std::vector<std::string> files = FileFilter("D:\\Unity4_7_WorkSpace\\DreamCast_Client\\client\\Unity", fi);
	
	vector<string>::iterator iter;
	vector<string> data;
	for (iter = files.begin(); iter != files.end(); iter++)
	{
		//cout << *iter << endl;
		string s = *iter;		
		vector<string> content = GetFileContent(s);			
		vector<string> d= GetCodeClassName(content);				//找到包含有class 的语句

		for (vector<string>::iterator it = d.begin();it!=d.end();it++ )
		{
			data.push_back(*it);
		}
	}


	cout << endl << "class 个数：" << data.size() << endl;
	return 0;
}


vector<string> GetCodeClassName(vector<string> code)
{
	vector<string> classLines;
	vector<string>::iterator iter;
	for (iter = code.begin(); iter != code.end(); iter++)
	{
		string key = "class";
		string a = *iter;
		string::size_type idx;

		idx = a.find(key);//在a中查找b.

		if (idx != string::npos)//存在。
		{
			classLines.push_back(*iter);
		}		
	}
	;
	return classLines;
}
