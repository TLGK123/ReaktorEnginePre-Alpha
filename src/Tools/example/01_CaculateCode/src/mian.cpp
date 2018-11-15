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
	for (iter = files.begin(); iter != files.end(); iter++)
	{
		//cout << *iter << endl;
		string s = *iter;
		;
		long count = FileCharacter(s);
		todayWork += count;
		cout  <<"行数："<<count <<"  --  "<< *iter <<endl;
		;
	}

	cout << endl << "文件个数：" << files.size() << " 总计行数: " << todayWork << endl;
	return 0;
}
