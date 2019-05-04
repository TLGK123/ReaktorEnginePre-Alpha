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
    std::string str[] = {".cpp",".cs",".hpp" };
 	std::vector<string> fi(str,str+3);
	std::vector<std::string> files = FileFilter("/Users/blue/Desktop/GitHub/Vulkan", fi);
	
	vector<string>::iterator iter;
	for (iter = files.begin(); iter != files.end(); iter++)
	{
		//cout << *iter << endl;
		string s = *iter;
		;
		long count = FileCharacter(s);
		todayWork += count;
		cout  <<"ÐÐ- "<<count <<"  --  "<< *iter <<endl;
		;
	}

	cout << endl << " " << files.size()<<"   ww  "  << todayWork << endl;
	return 0;
}
